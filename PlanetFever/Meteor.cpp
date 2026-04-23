#include "Meteor.h"
#include "Scroll.h"
#include "CircleHitBox.h"
#include "Physics2D.h"
#include "Effect.h"
#include "PlanetInfo.h"
#include "SaveData.h"

Meteor::Meteor(PlanetInfo::OreType type ,Vector2 dir, float dist) :
	Actor2D("Resource/meteors.png", Tag::Enemy, Layer::Object, Vector2()),
	m_hp(0),
	m_seBreak(0),
	m_destroyWaitTimeFrame(DestroyWaitTimeFrame),
	m_isStartDestroy(false),
	m_type(type)
{
	// 位置や物理を設定
	m_transform.position = 
		dir.Normalized() * dist
		+ Physics2D::GetInstance()->GetGravityPoint();
	m_collider = new CircleHitBox(Radius,Vector2(), PhysicsBehavior::Collision);
	m_collider->SetPhysicsBehavior(Tag::Player, PhysicsBehavior::Trigger);
	m_collider->SetPhysicsBehavior(Tag::Ground, PhysicsBehavior::Collision);
	m_collider->SetPhysicsBehavior(Tag::Ore, PhysicsBehavior::Ignore);
	m_circleRigid2d = CircleRigid2D();
	m_circleRigid2d.limitSpeedFall = 1.25f;

	// アニメーション関連の設定
	m_sprite->SetGlidSize(GlidSize);
	m_sprite->SetAnimeType(static_cast<int>(m_type));

	// 隕石の種類や惑星の種類に応じて耐久力を設定
	int baseHp = static_cast<int>(PlanetInfo::MeteorHP[static_cast<int>(m_type)]);

	m_hp = baseHp;

	m_transform.scale = 2.0f;
}

void Meteor::Load()
{
	Scroll::GetInstance()->Register(this);

	m_seBreak = LoadSoundMem("Sounds/se_break.mp3", DX_PLAYTYPE_BACK);

	Actor2D::Load();
}

void Meteor::Release()
{
	Scroll::GetInstance()->Remove(this);

	DeleteSoundMem(m_seBreak);

	Actor2D::Release();
}

void Meteor::Update()
{
	if (!m_isStartDestroy) return;
	m_destroyWaitTimeFrame--;
	if (m_destroyWaitTimeFrame <= 0)
	{
		Destroy();
	}

	Actor2D::Update();
}

void Meteor::Draw()
{
	Actor2D::Draw();
}

void Meteor::OnCollisionEnter(const Actor2D* other)
{
	if (other->GetTag() == Tag::Ground)
	{
		StartDestroy();
	}

	if (other->GetTag() == Tag::Bullet)
	{
		m_hp -= 10;
		if (m_hp <= 0)
		{
			GetParent()->AddChild(new Ore(m_transform.position, m_type));

			StartDestroy();
		}
	}
}

void Meteor::StartDestroy()
{
	// 隕石の破片生成
	for (int i = 0; i < EffectAmount; i++)
	{
		float deg = static_cast<float>(rand() % 360);
		float rad = Math::Deg2Rad(deg);

		Vector2 dir = Vector2::AngleToDirect(deg);

		float power = static_cast<float>(fmod(rand(), MaxEffectPower - MinEffectPower) + MinEffectPower);

		GetParent()->AddChild(
			new Effect(
				Transform2D(
					m_transform.position,
					rad,
					m_transform.scale
				),
				Effect::Anime::Meteor,
				dir,
				power
			)
		);
	}

	PlaySoundMem(m_seBreak, DX_PLAYTYPE_BACK);

	m_collider->SetAllPhysicsBehavior(PhysicsBehavior::Ignore);

	m_isStartDestroy = true;

	m_sprite->SwitchDraw(false);

	Scroll::GetInstance()->ScreenShake();
}
