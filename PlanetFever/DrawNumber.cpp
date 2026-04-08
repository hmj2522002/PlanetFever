#include "DrawNumber.h"
#include <string>


DrawNumber::DrawNumber() :
	m_numberFont(0)
{
	m_numberFont = LoadGraph("Resource/number.png");
}

void DrawNumber::Release()
{
	DeleteGraph(m_numberFont);
}

void DrawNumber::Draw(float drawNum, Vector2 position, bool center, float scale, bool contain0) const
{
	int value = std::round(drawNum);
	int drawCount = 0;
	float drawX = 0;

	if (center)
	{
		int drawLength = std::to_string(static_cast<int>(drawNum)).length();

		if (drawLength < MinDrawLength)
		{
			drawLength = MinDrawLength;
		}
		// ƒYƒŒ’²®
		drawLength++;

		drawX = -(drawLength * (GlidSize.x * scale / 2.0f));
	}

	do
	{
		// ”’l•`‰æA¬‚³‚¢ˆÊ‚©‚ç‡‚É
		drawCount++;
		int drawNum = value % 10;
		drawX += GlidSize.x * scale;

		DrawRectRotaGraph(
			static_cast<int>(position.x - drawX),
			static_cast<int>(position.y),
			static_cast<int>(drawNum * GlidSize.x),
			0,
			static_cast<int>(GlidSize.x),
			static_cast<int>(GlidSize.y),
			static_cast<double>(scale),
			0.0,
			m_numberFont,
			true
		);

		value /= 10;
	} while (0 < value || (drawCount < 2 && contain0));

}
