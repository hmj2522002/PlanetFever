#include "Actor2D.h"
#include "CircleHitBox.h"
#include "Animation2D.h"
#include "Physics2D.h"

Actor2D::Actor2D(
	const char* handle,
	Tag tag,
	Layer layer,
	const Transform2D& transform,
	int tiles,
	int speed,
	bool loopFlag
) :
	m_tag(tag),
	m_layer(layer),
	m_sprite(nullptr),
	m_transform(transform),
	m_collider(nullptr)
{
	m_transform.scale = 1;

	m_sprite = new Animation2D(handle, tiles, speed, loopFlag);
}


void Actor2D::Load()
{
	if (m_sprite)
	{
		m_sprite->Load();
	}

	if (m_collider)
	{
		Physics2D::GetInstance()->Register(this);
	}
}

void Actor2D::Release()
{
	if (m_sprite)
	{
		delete m_sprite;
		m_sprite = nullptr;
	}

	if (m_collider)
	{
		Physics2D::GetInstance()->Remove(this);
		delete m_collider;
		m_collider = nullptr;
	}
}

void Actor2D::Update()
{
	if (m_sprite)
	{
		m_sprite->Update();
	}
}

void Actor2D::Draw()
{
	if (m_sprite)
	{
		m_sprite->Draw(m_transform, m_layer);
	}
}

void Actor2D::LateDraw()
{
	if (m_sprite)
	{
		m_sprite->LateDraw(m_transform, m_layer);
	}
}

void Actor2D::TreeUpdate()
{
	// Node–{—ˆ‚ÌTreeUpdate‚ðŽÀs
	Node::TreeUpdate();

	if (m_sprite)
	{
		m_sprite->Update();
	}
}
