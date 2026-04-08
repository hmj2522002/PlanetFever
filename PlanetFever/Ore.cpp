#include "Ore.h"
#include "CircleHitBox.h"
#include "GameInfo.h"
#include "Effect.h"

Ore::Ore(Vector2& position, PlanetInfo::OreType type) :
	Actor2D("Resource/ores.png", Tag::Ore, Layer::Object),
	m_type(type)
{
	m_collider = new CircleHitBox(Radius);
	m_transform.position = position;
	m_transform.scale = Scale;

	m_sprite->SetGlidSize(GlidSize);
	m_sprite->SetAnimeType(static_cast<int>(type));
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

		GetParent()->AddChild(new Effect(m_transform, Effect::Anime::Glow));

		Release();
	}
}
