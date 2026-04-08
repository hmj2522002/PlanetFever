#pragma once
#include "Transform2D.h"
#include "Node.h"

class DrawNumber : public Node
{
private:
	static constexpr Vector2 GlidSize = Vector2(30, 50);
	static constexpr int MinDrawLength = 2;

	int m_numberFont;

public:
	DrawNumber();

	void Release();
	void Draw(float drawNum, Vector2 position, bool center = true, float scale = 1.0f, bool contain0 = true) const;

};
