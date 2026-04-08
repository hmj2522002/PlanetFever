#include "SmallText.h"

SmallText::SmallText(Text text) :
	m_text(text)
{
	m_handle = LoadGraph("Resource/smallText.png");
}

void SmallText::Release()
{
	DeleteGraph(m_handle);
}

void SmallText::Draw(Vector2 position, float scale) const
{
	DrawRectRotaGraph(
		static_cast<int>(position.x),
		static_cast<int>(position.y),
		0,
		static_cast<int>(GlidSize.y) * static_cast<int>(m_text),
		static_cast<int>(GlidSize.x),
		static_cast<int>(GlidSize.y),
		static_cast<double>(scale),
		0.0,
		m_handle,
		true
	);
}
