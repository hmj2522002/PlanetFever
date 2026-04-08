#pragma once
#include "Actor2D.h"

class Ore : public Actor2D
{
public:
	enum class OreType
	{
		Coal,	// êŒíY
		Silver,	// ã‚
		Iron,	// ìS
		Copper,	// ì∫
		Gold,	// ã‡
	};

	OreType m_type;

private:
	static constexpr int Radius = 4;
	static constexpr Vector2 GlidSize = Vector2(16, 16);

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual void OnCollisionEnter(const Actor2D* other) override;

public:
	Ore(Vector2& position, OreType type);

};
