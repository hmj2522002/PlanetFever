#pragma once
#include "Actor2D.h"

class Rocket : public Actor2D
{
private:
	static constexpr float Radius = 25.0f;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	Rocket();

};
