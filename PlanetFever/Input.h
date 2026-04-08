#pragma once
#include "KeyBoard.h"
#include "Mouse.h"

class Input
{
private:
	Input(){}

public:
	static void Update()
	{
		Keyboard::Update();
		Mouse::Update();
	}
};
