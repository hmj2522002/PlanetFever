#include "Meteor.h"
#include "Scroll.h"
#include "CircleHitBox.h"
#include "Physics2D.h"
#include "Effect.h"
#include "PlanetInfo.h"
#include "SaveData.h"

Meteor::Meteor(PlanetInfo::OreType type ,Vector2 dir) :
	Actor2D("Resource/meteors.png", Tag::Enemy, Layer::Object, Vector2()),
	m_hp(0),
	m_seBreak(0),
	m_destroyWaitTimeFrame(DestroyWaitTimeFrame),
	m_isStartDestroy(false),
	m_type(type)
{
	m_transform.position = 
		dir.Normalized() * 1000
		+ Physics2D::GetInstance()->GetGravityPoint();
	m_collider = new CircleHitBox(Radius,Vector2(), PhysicsBehavior::Collision);
	m_collider->SetPhysicsBehavior(Tag::Player, PhysicsBehavior::Trigger);
	m_collider->SetPhysicsBehavior(Tag::Ground, PhysicsBehavior::Collision);
	m_collider->SetPhysicsBehavior(Tag::Ore, PhysicsBehavior::Ignore);
	m_circleRigid2d = CircleRigid2D();
	m_circleRigid2d.limitSpeedFall = 1.0f;

	m_sprite->SetGlidSize(GlidSize);
	m_sprite->SetAnimeType(static_cast<int>(m_type));

	float baseHp = PlanetInfo::MeteorHP[static_cast<int>(m_type)];

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
		m_hp -= 1.0f;
		if (m_hp <= 0)
		{
			GetParent()->AddChild(new Ore(m_transform.position, m_type));

			StartDestroy();
		}
	}
}

void Meteor::StartDestroy()
{
	for (int i = 0; i < EffectAmount; i++)
	{
		Vector2 dir = Vector2::AngleToDirect(rand() % 360);

		float power = fmod(rand(), MaxEffectPower - MinEffectPower) + MinEffectPower;

		GetParent()->AddChild(
			new Effect(
				Transform2D(
					m_transform.position,
					Math::Deg2Rad(dir).ToRad(),
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
