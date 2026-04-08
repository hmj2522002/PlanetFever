#include "Ore.h"
#include "CircleHitBox.h"
#include "GameInfo.h"

Ore::Ore(Vector2& position, OreType type) :
	Actor2D("Resource/ores.png", Tag::Ore, Layer::Object),
	m_type(type)
{
	m_collider = new CircleHitBox(Radius);
	m_transform.position = position;

	m_sprite->SetGlidSize(GlidSize);
}

void Ore::Load()
{
	Scroll::GetInstance()->Register(this);

	Actor2D::Load();
}

void Ore::Release()
{
	Scroll::GetInstance()->Remove(this);

	Actor2D::Release();
}

void Ore::Update()
{
	Actor2D::Update();
}

void Ore::Draw()
{
	Actor2D::Draw();
}

void Ore::OnCollisionEnter(const Actor2D* other)
{
	if (other->GetTag() == Tag::Player)
	{
		GameInfo::GetInstance()->AddCollectOre(m_type, 1);

		Release();
	}
}
