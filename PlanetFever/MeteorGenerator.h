#pragma once
#include "Node.h"
#include "Vector2.h"

class MeteorGenerator : public Node
{
private:
	static constexpr int DefaultSpanFrame = 180;
	static constexpr int FinishSpawnFrame = 1000;

	Vector2 m_spawnDir;
	int m_spanFrame;
	int m_deltaFrame;
	int dummy = 0;

protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;

public:
	MeteorGenerator();
};
