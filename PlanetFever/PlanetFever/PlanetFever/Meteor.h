#pragma once
#include "Actor2D.h"
#include "Ore.h"

class Meteor : public Actor2D
{
private:
	static constexpr float Radius = 25;
	static constexpr Vector2 GlidSize = Vector2(70, 70);

	int m_hp;
	Ore::OreType m_type;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual void OnCollisionEnter(const Actor2D* other) override;

public:
	Meteor(Ore::OreType type ,Vector2 dir);

};
