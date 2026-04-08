#pragma once
#include "Actor2D.h"
#include "Ore.h"

class Meteor : public Actor2D
{
private:
	static constexpr Vector2 GlidSize = Vector2(70, 70);
	static constexpr float Radius = 25;
	static constexpr float MinEffectPower = 0.8f;
	static constexpr float MaxEffectPower = 2.2f;
	static constexpr int EffectAmount = 8;
	static constexpr int DestroyWaitTimeFrame = 180;

	int m_hp;
	int m_seBreak;
	int m_destroyWaitTimeFrame;
	bool m_isStartDestroy;
	PlanetInfo::OreType m_type;

	void StartDestroy();

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

	virtual void OnCollisionEnter(const Actor2D* other) override;

public:
	Meteor(PlanetInfo::OreType type ,Vector2 dir);

};
