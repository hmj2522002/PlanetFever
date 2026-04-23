#include "ScoreUI.h"
#include "GameInfo.h"
#include "SmallText.h"

ScoreUI::ScoreUI() :
	m_score(0),
	m_numberFont(0),
	m_drawScore(0),
	m_smallText(nullptr)
{
	m_numberFont = LoadGraph("Resource/number.png");

	m_drawScore = static_cast<float>(GameInfo::GetInstance()->GetPrevTotalScore());
	m_score = SaveData::GetInstance()->GetScore();

	m_smallText = new SmallText(SmallText::Text::Score);
	AddChild(m_smallText);

	m_drawNumber = new DrawNumber();
	AddChild(m_drawNumber);
}

void ScoreUI::Load()
{
	
}

void ScoreUI::Release()
{

}

void ScoreUI::Update()
{
	// •`‰æŽž‚É‚ä‚Á‚­‚è‚Æ–{—ˆ‚Ì”’l‚É•Ï‚¦‚é
	m_drawScore += (m_score - m_drawScore) * 0.05f;
}

void ScoreUI::LateDraw()
{
	m_drawNumber->Draw(m_drawScore, Position + ScoreOffset, false);
	m_smallText->Draw(Position + TextOffset);
}
