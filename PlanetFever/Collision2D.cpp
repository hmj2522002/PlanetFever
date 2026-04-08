#include "Collision2D.h"
#include "Transform2D.h"
#include "CircleHitBox.h"
#include "Math.hpp"

Collision2D::Circle::Circle(const Transform2D& transform, const CircleHitBox* hitBox) :
	center(transform.position + hitBox->offset * transform.scale),
	radius(hitBox->radius * transform.scale)
{

}

const Collision2D::HitInfo Collision2D::CheckCircleHitBoxes(
	const Transform2D& hitBoxT1, const CircleHitBox* hitBoxH1,
	const Transform2D& hitBoxT2, const CircleHitBox* hitBoxH2)
{
	HitInfo hitInfo;
	float dist;

	dist = std::powf((hitBoxT1.position.x + hitBoxH1->offset.x) - (hitBoxT2.position.x + hitBoxH2->offset.x), 2.0f) +
		   std::powf((hitBoxT1.position.y + hitBoxH1->offset.y) - (hitBoxT2.position.y + hitBoxH2->offset.y), 2.0f);

	float r = hitBoxH1->radius * hitBoxT1.scale + hitBoxH2->radius * hitBoxT2.scale;

	hitInfo.isHit = dist <= std::powf(r, 2.0f);

	return hitInfo;
}

