#include "ScoreUI.h"
#include "GameInfo.h"

ScoreUI::ScoreUI() :
	m_score(0),
	m_numberFont(0),
	m_drawScore(0)
{
	m_numberFont = LoadGraph("Resource/number.png");

	m_drawScore = GameInfo::GetInstance()->GetPrevTotalScore();
	m_score = SaveData::GetInstance()->GetScore();
}

void ScoreUI::Load()
{
	
}

void ScoreUI::Release()
{

}

void ScoreUI::Update()
{
	m_drawScore += (m_score - m_drawScore) * 0.05f;
}

void ScoreUI::LateDraw()
{
	int value = std::round(m_drawScore);
	int drawCount = 0;
	float drawX = 0;

	do
	{	// éûä‘êßå¿UIï`âÊ
		drawCount++;
		int drawNum = value % 10;
		drawX += GlidSize.x;

		DrawRectRotaGraph(
			Position.x + Offset.x - drawX,
			Position.y + Offset.y,
			drawNum * GlidSize.x,
			0,
			GlidSize.x,
			GlidSize.y,
			1.0,
			0.0,
			m_numberFont,
			true
		);

		value /= 10;
	} while (0 < value || drawCount < 2);

	Node::LateDraw();

	DrawFormatString(0, 400, GetColor(200, 244, 15), "m_drawScore %f", m_drawScore);
}
