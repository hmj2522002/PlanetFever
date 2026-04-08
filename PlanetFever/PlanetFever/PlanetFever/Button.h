#pragma once
#include "Actor2D.h"
#include "Transform2D.h"
#include <functional>

class Button
{
private:
	Actor2D* m_target;
	int m_pressMouse;
	float m_radius;
	float m_mouseDist;
	bool m_isHolding;
	Transform2D m_transform;

protected:

public:
	Button(Actor2D* target, float rad, int mouse = MOUSE_INPUT_LEFT);

	void Update();

	bool IsCursorIn();
	bool IsDown();
	bool IsPress();
	bool IsUp();
	bool IsDownToUp();

};
