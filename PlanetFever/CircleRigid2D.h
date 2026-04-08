#pragma once
#include "Vector2.h"

class CircleRigid2D
{
public:
	// 動作モード
	enum class BodyType
	{
		Dynamic,	
		Kinematic,
		Static,		
	};

	Vector2 velocity;	// 速度
	float gravityScale;	// 重力の影響度合
	float mass;			// 重さ
	float horizontalFriction;	// 横方向ブレーキ
	float limitSpeedFall;	// 重力の最大落下数
	bool gravityLimit;	// 重力の制限
	bool isHorizontalFriction;	// 横方向減速させるか

private:
	BodyType m_bodyType;	// 動作モード

public:
	CircleRigid2D(
		BodyType bodyType = BodyType::Dynamic,
		float gravityScale = 1.0f,
		float mass = 1.0f,
		bool gravityLimit = true
	) :
		m_bodyType(bodyType),
		gravityScale(gravityScale),
		mass(mass),
		gravityLimit(gravityLimit),
		horizontalFriction(0.1f),
		limitSpeedFall(2.0f),
		isHorizontalFriction(true){ }

	void AddForce(const Vector2& force) { velocity += force; }

	const BodyType GetBodyType() const { return m_bodyType; }
};
