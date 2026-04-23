#include "Player.h"
#include "CircleHitBox.h"
#include "Input.h"
#include "Physics2D.h"
#include "Scroll.h"
#include "Bullet.h"
#include "GameInfo.h"
#include "Effect.h"

Player::Player(Vector2 pos) :
	Actor2D("Resource/player.png", Tag::Player, Layer::Object, Screen::Center, 2, 2),
	m_jetPackSpeed(0),
	m_horizontalSpeed(0),
	m_prevAnimType(-1),
	m_seFire(0),
	m_seDamage(0),
	m_seJet(0),
	m_stunTimeFrame(0),
	m_isGrounded(false),
	m_prevGrounded(false),
	m_isJet(false),
	m_prevJet(false)
{
	m_collider = new CircleHitBox(HitBox::Radius, HitBox::Offset, PhysicsBehavior::Collision);
	m_collider->SetPhysicsBehavior(Tag::Bullet, PhysicsBehavior::Ignore);

	m_circleRigid2d = CircleRigid2D(CircleRigid2D::BodyType::Dynamic);
	m_sprite->SetGlidSize(GlidSize);

	m_transform.position = pos;
}

void Player::Load()
{
	Scroll::GetInstance()->Register(this);

	m_seFire = LoadSoundMem("Sounds/se_fire.mp3");
	m_seDamage = LoadSoundMem("Sounds/se_damage.mp3");
	m_seJet = LoadSoundMem("Sounds/se_jet.mp3");

	ChangeVolumeSoundMem(160, m_seFire);

	Actor2D::Load();
}

void Player::Release()
{
	Scroll::GetInstance()->Remove(this);

	DeleteSoundMem(m_seFire);
	DeleteSoundMem(m_seDamage);
	DeleteSoundMem(m_seJet);

	Actor2D::Release();
}

void Player::Update()
{
	Actor2D::Update();

	Vector2 gravityPoint = Physics2D::GetInstance()->GetGravityPoint();
	Vector2 dir;

	Vector2 mousePoint = Mouse::GetPoint();
	Vector2 scrollPos = Scroll::GetInstance()->GetPosition();
	float cameraScale = Scroll::GetInstance()->GetCameraScale();

	GameInfo* gameInfo = GameInfo::GetInstance();

	Anime anime = Anime::Stand;
	
	m_mouseWorldPoint = (mousePoint - Screen::Center) / cameraScale +
		scrollPos;

	bool isTimeUp = gameInfo->IsTimeUp();



	if (m_isGrounded)
	{
		dir = (m_transform.position - gravityPoint);
		m_circleRigid2d.horizontalFriction = 0.1f;

	}
	else
	{
		if (gameInfo->InGame() && m_stunTimeFrame <= 0)
		{
			dir = (m_mouseWorldPoint - m_transform.position);
			anime = Anime::Fly;
		}
		else
		{
			dir = (m_transform.position - gravityPoint);
			anime = Anime::Fall;
		}
		m_circleRigid2d.horizontalFriction = 0.01f;
	}
	m_transform.angle = dir.Normalized().ToRad() + 
		static_cast<float>(Math::Pi) / 2.0f;

	// 惑星に垂直な移動の速度を取得
	Vector2 tangent = Vector2(-dir.y, dir.x).Normalized();
	m_horizontalSpeed = Vector2::Dot(m_circleRigid2d.velocity, tangent);
	
	// 一定速度に達したら歩きモーション
	if (m_isGrounded && StartWalkSpeed < Math::Abs(m_horizontalSpeed)) 
	{
		anime = Anime::Walk; 

		// 左に移動していたら画像反転
		m_sprite->SwitchFlipX(m_horizontalSpeed < 0);
	}
	
	m_isJet = false;

	if (Mouse::IsPress(MOUSE_INPUT_LEFT) && gameInfo->InGame() && m_stunTimeFrame <= 0)
	{
		Vector2 nowVelocity;
		nowVelocity = m_circleRigid2d.velocity;

		m_circleRigid2d.gravityLimit = false;

		m_circleRigid2d.gravityScale = 0.0f;
		Vector2 diff = (m_mouseWorldPoint - m_transform.position).Normalized();

		nowVelocity = nowVelocity + diff * JetPackBoost;

		if (MaxJetPackSpeed <= nowVelocity.Magnitude())
		{
			nowVelocity = nowVelocity.Normalized() * MaxJetPackSpeed;
		}
		else
		{

		}

		m_circleRigid2d.velocity = nowVelocity;

		if (!m_isGrounded)
		{
			m_isJet = true;

			float spread = MaxEffectPower - MinEffectPower;

			Vector2 random = Vector2(
				fmod(rand(), spread) - spread / 2.0f,
				fmod(rand(), spread) - spread / 2.0f
			);

			float power = random.x * 2.0f;
			Vector2 rotation = random + Vector2(
				MaxEffectPower - MinEffectPower,
				MaxEffectPower - MinEffectPower) / 2.0f;

			AddChild(new Effect(
				m_transform,
				Effect::Anime::Air,
				-diff + rotation,
				power
			));
		}
	}
	else
	{
		m_circleRigid2d.gravityScale = 1.0f;
		m_circleRigid2d.gravityLimit = true;
	}

	if (m_isJet && !m_prevJet)
	{
		PlaySoundMem(m_seJet, DX_PLAYTYPE_LOOP);
	}
	if (!m_isJet && m_prevJet)
	{
		StopSoundMem(m_seJet);
	}

	if (GameInfo::GetInstance()->InGame() && m_stunTimeFrame <= 0 && !m_isGrounded)
	{
		if (Keyboard::IsDown(KEY_INPUT_SPACE) ||
			Keyboard::IsUp(KEY_INPUT_SPACE))
		{
			GetParent()->AddChild(new Bullet(m_transform));
			PlaySoundMem(m_seFire, DX_PLAYTYPE_BACK);
		}
	}

	// アニメーション切り替え管理
	if (m_prevAnimType != static_cast<int>(anime))
	{
		SetAnimeType(anime);
	}

	if (0 < m_stunTimeFrame)
	{
		m_stunTimeFrame--;
	}

	m_prevAnimType = m_sprite->GetAnimeType();
	m_prevGrounded = m_isGrounded;
	m_prevJet = m_isJet;
}

void Player::Draw()
{
	Actor2D::Draw();
}

void Player::SetAnimeType(Anime type)
{
	m_sprite->SetAnimeType(static_cast<int>(type));
	m_sprite->SetTiles(AnimeGlid[static_cast<int>(type)].tiles);
	m_sprite->SetSpeed(AnimeGlid[static_cast<int>(type)].speed);
	m_sprite->SwitchLoop(AnimeGlid[static_cast<int>(type)].loop);
}

void Player::OnCollisionEnter(const Actor2D* other)
{
	if (other->GetTag() == Tag::Ground)
	{
		m_isGrounded = true;
	}

	if (other->GetTag() == Tag::Enemy)
	{
		PlaySoundMem(m_seDamage, DX_PLAYTYPE_BACK);
		m_circleRigid2d.velocity = (m_transform.position - other->GetPosition()).Normalized() * DamageKnockBackPower;
		m_stunTimeFrame = StunTimeFrame;
	}
}

void Player::OnCollision(const Actor2D* other)
{
}

void Player::OnCollisionExit(const Actor2D* other)
{
	if (other->GetTag() == Tag::Ground)
	{
		m_isGrounded = false;
	}
}
