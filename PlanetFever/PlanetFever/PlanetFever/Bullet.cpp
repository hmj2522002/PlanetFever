#include "Bullet.h"
#include "CircleHitBox.h"

Bullet::Bullet(Transform2D& transform, BulletType bulletType) :
	Actor2D("Resource/bullet.png", Tag::Bullet, Layer::Object, transform, 2, 30),
	m_lifeTimeFrame(LifeTimeFrame)
{
	m_collider = new CircleHitBox(Radius);

	m_sprite->SetGlidSize(GlidSize);

	m_circleRigid2d = CircleRigid2D(CircleRigid2D::BodyType::Kinematic);
	m_circleRigid2d.velocity = Vector2::AngleToDirect(Math::Rad2Deg(-transform.angle + Math::Pi / 2.0f)) * Speed;
}

void Bullet::Load()
{
	Actor2D::Load();
}

void Bullet::Release()
{
	Actor2D::Release();
}

void Bullet::Update()
{
	m_lifeTimeFrame--;
	if (m_lifeTimeFrame <= 0)
	{
		Release();
	}

	Actor2D::Update();
}

void Bullet::Draw()
{
	Actor2D::Draw();
}

void Bullet::OnCollisionEnter(const Actor2D* other)
{
	if (other->GetTag() == Tag::Enemy ||
		other->GetTag() == Tag::Ground)
	{
		Release();
	}
}
