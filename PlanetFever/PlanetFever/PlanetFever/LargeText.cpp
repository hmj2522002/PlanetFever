#include "LargeText.h"

LargeText::LargeText(Text text, Vector2 position, bool blinking) :
	m_text(text),
	m_position(position),
	m_isBlinking(blinking)
{
	m_handle = LoadGraph("Resource/largeText.png");
}

void LargeText::Load()
{
	
}

void LargeText::Release()
{

}

void LargeText::Update()
{

}

void LargeText::LateDraw()
{
	DrawRectRotaGraph(
		static_cast<int>(m_position.x),
		static_cast<int>(m_position.y),
		0,
		static_cast<int>(GlidSize.y) * static_cast<int>(m_text),
		static_cast<int>(GlidSize.x),
		static_cast<int>(GlidSize.y),
		1.0,
		0.0,
		m_handle,
		true
	);
}
