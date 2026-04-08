#pragma once
#include "Vector2.h"

class CircleHitBox;
class Transform2D;

class Collision2D
{
private:
	struct Circle
	{
		Vector2 center;
		float radius;

		Circle(const Transform2D& transform, const CircleHitBox* hitBox);
	};

public:
	struct HitInfo
	{
		bool isHit;

		HitInfo() :
			isHit(false){}
	};

	// CircleHitBox “¯Žm‚Ì”»’è
	static const HitInfo CheckCircleHitBoxes(
		const Transform2D& hitBoxT1, const CircleHitBox* hitBoxH1,
		const Transform2D& hitBoxT2, const CircleHitBox* hitBoxH2);

};
