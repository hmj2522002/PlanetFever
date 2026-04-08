#pragma once
#include "Actor2D.h"
#include "PlanetInfo.h"

class Ore : public Actor2D
{
private:
	static constexpr float Scale = 1.5f;
	static constexpr int Radius = 4;
	static constexpr Vector2 GlidSize = Vector2(16, 16);

	PlanetInfo::OreType m_type;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual void OnCollisionEnter(const Actor2D* other) override;

public:
	Ore(Vector2& position, PlanetInfo::OreType type);

};
