#include "TimeLeftUI.h"
#include "GameInfo.h"

TimeLeftUI::TimeLeftUI() :
	m_timeLeft(0),
	m_numberFont(0)
{
	m_numberFont = LoadGraph("Resource/number.png");
}

void TimeLeftUI::Load()
{
	Node::Load();
}

void TimeLeftUI::Release()
{
	Node::Release();
}

void TimeLeftUI::Update()
{
	m_timeLeft = GameInfo::GetInstance()->GetTimeLeft();

	Node::Update();
}

void TimeLeftUI::Draw()
{
	Node::Draw();
}

void TimeLeftUI::LateDraw()
{
	int value = m_timeLeft;
	int drawCount = 0;
	float drawX = 0;

	do
	{	// éûä‘êßå¿UIï`âÊ
		drawCount++;
		int drawNum = value % 10;
		bool isSmall = drawCount <= SmallNumAmount;
		drawX += GlidSize.x * (isSmall ? SmallScale : 1);

		DrawRectRotaGraph(
			static_cast<int>(Position.x) + static_cast<int>(Offset.x - drawX),
			static_cast<int>(Position.y) + static_cast<int>(Offset.y + (GlidSize.y / 2.0f * (1 - SmallScale)) * isSmall),
			drawNum * static_cast<int>(GlidSize.x),
			0,
			static_cast<int>(GlidSize.x),
			static_cast<int>(GlidSize.y),
			isSmall ? SmallScale : 1.0,
			0.0,
			m_numberFont,
			true
		);

		value /= 10;
	} while (0 < value || drawCount < 3);

	Draw();
}
