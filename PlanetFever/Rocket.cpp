#include "Rocket.h"
#include "CircleHitBox.h"
#include "Player.h"

Rocket::Rocket() :
	Actor2D("Resource/rocket.png", Tag::None, Layer::Object),
	m_playerSpawnTimeFrame(PlayerSpawnTimeFrame)
{
	m_transform.position = Screen::Center + Vector2(0, -200);

	m_collider = new CircleHitBox(Radius);
	m_collider->SetAllPhysicsBehavior(PhysicsBehavior::Ignore);
	m_collider->SetPhysicsBehavior(Tag::Ground, PhysicsBehavior::Collision);
}

void Rocket::Load()
{
	Actor2D::Load();
}

void Rocket::Release()
{
	Actor2D::Release();
}

void Rocket::Update()
{
	if (m_playerSpawnTimeFrame <= 0) return;

	m_playerSpawnTimeFrame--;
	if (m_playerSpawnTimeFrame <= 0)
	{
		GetParent()->AddChild(new Player(m_transform.position));
	}

	Actor2D::Update();
}

void Rocket::Draw()
{
	Actor2D::Draw();
}
