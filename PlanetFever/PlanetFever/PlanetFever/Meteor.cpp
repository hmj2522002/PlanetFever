#include "Meteor.h"
#include "Scroll.h"
#include "CircleHitBox.h"
#include "Physics2D.h"

Meteor::Meteor(Ore::OreType type ,Vector2 dir) :
	Actor2D("Resource/meteors.png", Tag::Enemy, Layer::Object, Vector2()),
	m_hp(10),
	m_type(type)
{
	m_transform.position = 
		dir.Normalized() * 1000
		+ Physics2D::GetInstance()->GetGravityPoint();
	m_collider = new CircleHitBox(Radius,Vector2(), PhysicsBehavior::Collision);
	m_collider->SetPhysicsBehavior(Tag::Player, PhysicsBehavior::Trigger);
	m_collider->SetPhysicsBehavior(Tag::Ground, PhysicsBehavior::Collision);
	m_circleRigid2d = CircleRigid2D();
	m_circleRigid2d.limitSpeedFall = 1.0f;

	m_sprite->SetGlidSize(GlidSize);

	m_transform.scale = 2.0f;
}

void Meteor::Load()
{
	Scroll::GetInstance()->Register(this);


	Actor2D::Load();
}

void Meteor::Release()
{
	Scroll::GetInstance()->Remove(this);

	Actor2D::Release();
}

void Meteor::Update()
{
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
		Release();
	}

	if (other->GetTag() == Tag::Bullet)
	{
		m_hp--;
		if (m_hp <= 0)
		{
			GetParent()->AddChild(new Ore(m_transform.position, m_type));
			Release();
		}
	}
}
