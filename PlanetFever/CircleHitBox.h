#pragma once
#include "PhysicsBehavior.h"
#include "Tag.h"
#include "Collision2D.h"
#include <array>

class CircleHitBox
{
private:
	std::array<PhysicsBehavior, static_cast<int>(Tag::Length)>
		m_physicsBehavior;

public:
	Vector2 offset;
	float radius;

	CircleHitBox(float radius, const Vector2& offset = Vector2(), PhysicsBehavior behavior = PhysicsBehavior::Trigger) :
		radius(radius),
		m_physicsBehavior{behavior},
		offset(offset) {}

	void SetPhysicsBehavior(Tag tag, PhysicsBehavior pb) { m_physicsBehavior[static_cast<int>(tag)] = pb; }
	void SetAllPhysicsBehavior(PhysicsBehavior pb)
	{
		for (auto& ref : m_physicsBehavior)
		{
			ref = pb;
		}
	}

	PhysicsBehavior GetPhysicsBehavior(Tag tag) const { return m_physicsBehavior[static_cast<int>(tag)]; }



	Collision2D::HitInfo CheckHitBox(const Transform2D& t1, const Transform2D& t2, const CircleHitBox* hitBox) const
	{
		return Collision2D::CheckCircleHitBoxes(t1, this, t2, hitBox);
	}
};
