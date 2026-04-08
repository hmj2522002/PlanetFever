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

	static constexpr Vector2 Size = Vector2(Width, Height);
	static constexpr Vector2 Center = Size / 2;
}
