#include "Effect.h"
#include "CircleHitBox.h"

Effect::Effect(Transform2D transform, Anime anime, Vector2 dir, float power) :
	Actor2D("Resource/effects.png", Tag::None, Layer::Object),
	m_effectType(anime),
	m_lifeTimeFrame(LifeTimeFrame)
{
	m_transform = transform;
	m_collider = new CircleHitBox(Radius);
	m_circleRigid2d = CircleRigid2D(CircleRigid2D::BodyType::Kinematic);
	m_circleRigid2d.velocity = dir.Normalized() * power;

	m_collider->SetAllPhysicsBehavior(PhysicsBehavior::Ignore);

	m_sprite->SetGlidSize(GlidSize);
	m_sprite->SetAnimeType(static_cast<int>(m_effectType));

	m_sprite->SetAnimeType(static_cast<int>(m_effectType));
	m_sprite->SetTiles(AnimeGlid[static_cast<int>(m_effectType)].tiles);
	m_sprite->SetSpeed(AnimeGlid[static_cast<int>(m_effectType)].speed);
	m_sprite->SwitchLoop(AnimeGlid[static_cast<int>(m_effectType)].loop);
}

void Effect::Release()
{
	Actor2D::Release();
}

void Effect::Update()
{
	Actor2D::Update();

	m_lifeTimeFrame--;

	if (m_lifeTimeFrame <= 0
		|| m_sprite->GetIsLooped())
	{
		Destroy();
	}
}

void Effect::Draw()
{
	Actor2D::Draw();
}
