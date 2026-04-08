#include "Planet.h"
#include "Input.h"
#include "Scroll.h"
#include "Physics2D.h"
#include "PlanetInfo.h"
#include "CircleHitBox.h"

Planet::Planet() :
	Actor2D("Resource/planets.png", Tag::Ground, Layer::Object),
	m_radius(0),
	m_isHit(false)
{
	m_radius = PlanetInfo::GetInstance()->GetNowPlanetRadius();

	m_collider = new CircleHitBox(m_radius, Vector2(), PhysicsBehavior::Collision);
	m_circleRigid2d = CircleRigid2D(CircleRigid2D::BodyType::Static);

	m_sprite->SetGlidSize(GlidSize);

	m_transform.position = (Screen::Center);
}

void Planet::Load()
{
	Scroll::GetInstance()->SetPosition(m_transform.position);
	Physics2D::GetInstance()->SetGravityPoint(m_transform.position);

	Scroll::GetInstance()->Register(this);

	Actor2D::Load();
}

void Planet::Release()
{
	Scroll::GetInstance()->Remove(this);

	Actor2D::Release();
}

void Planet::Update()
{
	Actor2D::Update();
}

void Planet::Draw()
{
	Actor2D::Draw();
	DrawFormatString(700, 20, GetColor(255, 100, 100), "Planet : %d", m_collider->GetPhysicsBehavior(Tag::Player));
	DrawCircleAA(m_transform.position.x, m_transform.position.y, m_collider->radius, 50, GetColor(255, 0, 0), false);
}

void Planet::OnCollisionEnter(const Actor2D* other)
{
	if (other->GetTag() == Tag::Player)
	{
		m_isHit = true;
	}
}

void Planet::OnCollisionExit(const Actor2D* other)
{
	if (other->GetTag() == Tag::Player)
	{
		m_isHit = false;
	}
}
