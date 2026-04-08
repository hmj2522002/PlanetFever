#pragma once
#include "Vector2.h"

namespace Screen
{
	static constexpr int Width = 1024;
	static constexpr int Height = 768;

	static constexpr int Top = 0;
	static constexpr int Bottom = Screen::Height;
	static constexpr int Left = 0;
	static constexpr int Right = Screen::Width;

	static constexpr int WidthCenter = Screen::Width / 2;
	static constexpr int HeightCenter = Screen::Height / 2;

	static constexpr Vector2 Size = Vector2(Width, Height);
	static constexpr Vector2 Center = Size / 2;

	static constexpr Vector2 TopLeft = Vector2(Screen::Left, Screen::Top);
	static constexpr Vector2 TopCenter = Vector2(Screen::WidthCenter, Screen::Top);
	static constexpr Vector2 TopRight = Vector2(Screen::Right, Screen::Top);
	static constexpr Vector2 CenterLeft = Vector2(Screen::Left, Screen::HeightCenter);
	static constexpr Vector2 CenterCenter = Vector2(Screen::WidthCenter, Screen::HeightCenter);
	static constexpr Vector2 CenterRight = Vector2(Screen::Right, Screen::HeightCenter);
	static constexpr Vector2 BottomLeft = Vector2(Screen::Left, Screen::Bottom);
	static constexpr Vector2 BottomCenter = Vector2(Screen::WidthCenter, Screen::Bottom);
	static constexpr Vector2 BottomRight = Vector2(Screen::Right, Screen::Bottom);
}
