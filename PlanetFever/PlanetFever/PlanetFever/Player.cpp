#include "Player.h"
#include "CircleHitBox.h"
#include "Input.h"
#include "Physics2D.h"
#include "Scroll.h"
#include "Bullet.h"
#include "GameInfo.h"

Player::Player() :
	Actor2D("Resource/player.png", Tag::Player, Layer::Object, Screen::Center, 2, 2),
	m_jetPackSpeed(0),
	m_isGrounded(false)
{
	m_collider = new CircleHitBox(HitBox::Radius, HitBox::Offset, PhysicsBehavior::Collision);
	m_collider->SetPhysicsBehavior(Tag::Bullet, PhysicsBehavior::Ignore);

	m_circleRigid2d = CircleRigid2D(CircleRigid2D::BodyType::Dynamic);
	m_sprite->SetGlidSize(GlidSize);

	m_transform.position = Vector2(0, -500);
}

void Player::Load()
{
	Scroll::GetInstance()->Register(this);


	Actor2D::Load();
}

void Player::Release()
{
	Scroll::GetInstance()->Remove(this);

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
	
	m_mouseWorldPoint = (mousePoint - Screen::Center) / cameraScale +
		scrollPos;

	bool isTimeUp = GameInfo::GetInstance()->IsTimeUp();

	if (m_isGrounded)
	{
		dir = (m_transform.position - gravityPoint).Normalized();
		m_circleRigid2d.horizontalFriction = 0.1f;
	}
	else
	{
		dir = (m_mouseWorldPoint - m_transform.position).Normalized();
		m_circleRigid2d.horizontalFriction = 0.01f;
	}
	m_transform.angle = dir.ToRad() + 
		static_cast<float>(Math::Pi) / 2.0f;
	

	if (Mouse::IsAnyPress() && !isTimeUp)
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

		
	}
	else
	{
		m_circleRigid2d.gravityScale = 1.0f;
		m_circleRigid2d.gravityLimit = true;
	}

	if (!isTimeUp)
	{
		if (Keyboard::IsDown(KEY_INPUT_SPACE) ||
			Keyboard::IsUp(KEY_INPUT_SPACE))
		{
			GetParent()->AddChild(new Bullet(m_transform));
		}
	}
}

void Player::Draw()
{
	Actor2D::Draw();
	DrawFormatString(700, 0, GetColor(155, 100, 200), "PlayerMagnitude : %f", m_circleRigid2d.velocity.Magnitude());
	DrawFormatString(700, 200, GetColor(0, 100, 200), "PlayerPos : %f, %f", m_transform.position.x, m_transform.position.y);
	DrawFormatString(700, 220, GetColor(155, 0, 200), "MouseWPos : %f, %f", m_mouseWorldPoint.x, m_mouseWorldPoint.y);
	DrawFormatString(700, 240, GetColor(155, 100, 0), "MousePos : %f, %f", Mouse::GetPoint().x, Mouse::GetPoint().y);

	DrawCircleAA(m_transform.position.x, m_transform.position.y, m_collider->radius, 50, GetColor(255, 0, 0), false);

	DrawCircleAA(m_mouseWorldPoint.x, m_mouseWorldPoint.y, 10, 10, GetColor(255, 0, 0), false);
}

void Player::OnCollisionEnter(const Actor2D* other)
{
	if (other->GetTag() == Tag::Ground)
	{
		m_isGrounded = true;
	}
}

void Player::OnCollisionExit(const Actor2D* other)
{
	if (other->GetTag() == Tag::Ground)
	{
		m_isGrounded = false;
	}
}
