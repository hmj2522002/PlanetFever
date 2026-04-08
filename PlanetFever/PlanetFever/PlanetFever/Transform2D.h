#pragma once
#include "Vector2.h"

class Transform2D
{
public:
	Vector2 position;		// À•W
	float angle;			// Œü‚«(ƒ‰ƒWƒAƒ“)
	float scale;			// ‘å‚«‚³

	Transform2D() :
		angle(0),
		scale(1){}

	Transform2D(const Vector2& pos, float angle = 0, float scale = 1) :
		position(pos),
		angle(angle),
		scale(scale) {}
};
