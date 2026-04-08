#include "Fade.h"
#include "Screen.h"
#include "Easing.h"
#include "DxLib.h"

Fade::Fade() :
	m_isFade(false),
	m_height(0),
	m_elapsedTimeFrame(0),
	m_durationTimeFrame(0),
	m_beginHeight(0),
	m_endHeight(0),
	m_fadeColor(0)
{

}

void Fade::Update()
{
	if (!m_isFade) return;

	m_elapsedTimeFrame++;

	float time = static_cast<float>(m_elapsedTimeFrame) / m_durationTimeFrame;

	if (time >= 1.0f)
	{
		time = 1.0f;
		m_isFade = false;
	}

	m_height = Easing::EaseInCubic(m_beginHeight, m_endHeight, time);

	// åoâﬂéûä‘Ç©ÇÁçÇÇ≥ÇéZèo
	DrawBox(0, 0,
		Screen::Width, static_cast<int>(m_height),
		m_fadeColor,
		true);
}

void Fade::StartFadeIn(int color)
{
	m_fadeColor = color;

	m_elapsedTimeFrame = m_isFade ? 
		m_durationTimeFrame - m_elapsedTimeFrame :
		0;
	m_durationTimeFrame = DurationTimeFrame;
	m_beginHeight = Screen::Height;
	m_endHeight = 0;
	m_isFade = true;
}

void Fade::StartFadeOut(int color)
{
	m_fadeColor = color;

	m_elapsedTimeFrame = m_isFade ? 
		m_durationTimeFrame - m_elapsedTimeFrame :
		0;
	m_durationTimeFrame = DurationTimeFrame;
	m_beginHeight = 0;
	m_endHeight = Screen::Height;
	m_isFade = true;
}
