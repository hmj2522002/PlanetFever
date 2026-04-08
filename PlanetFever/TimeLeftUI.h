#pragma once
#include "Node.h"
#include "Vector2.h"
#include "Screen.h"

class TimeLeftUI : public Node
{
private:
	static constexpr Vector2 Offset = Vector2(60, 30);
	static constexpr Vector2 GlidSize = Vector2(30, 50);
	static constexpr Vector2 Position = Vector2(Screen::Width / 2.0f, 0);
	static constexpr int SmallNumAmount = 2;	// êîílÇè¨Ç≥Ç≠ï\é¶Ç≥ÇπÇÈêî
	static constexpr float SmallScale = 0.7f;

	int m_timeLeft;
	int m_numberFont;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void LateDraw() override;

public:
	TimeLeftUI();

};
