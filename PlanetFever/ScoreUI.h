#pragma once
#include "Node.h"
#include "Vector2.h"
#include "Screen.h"
#include "SmallText.h"
#include "DrawNumber.h"

class ScoreUI : public Node
{
private:
	static constexpr Vector2 ScoreOffset = Vector2(200, 60);
	static constexpr Vector2 TextOffset = Vector2(80, 20);
	static constexpr Vector2 GlidSize = Vector2(30, 50);
	static constexpr Vector2 Position = Vector2(Screen::Left, Screen::Top);

	SmallText* m_smallText;
	DrawNumber* m_drawNumber;
	int m_score;
	int m_numberFont;
	float m_drawScore;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateDraw() override;

public:
	ScoreUI();
};
