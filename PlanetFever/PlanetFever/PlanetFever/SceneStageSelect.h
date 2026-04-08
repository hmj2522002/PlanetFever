#pragma once
#include "SceneBase.h"
#include "Node.h"
#include "Vector2.h"

class SceneStageSelect : public SceneBase
{
private:
	static constexpr Vector2 TextOffset = Vector2(0, -200);
	static constexpr int MaxShowPlanetAmount = 5;
	static constexpr int MaxScrollSpeed = 60;
	static constexpr int FixScrollSpeed = 8;
	static constexpr float ScrollSpeedDown = 0.25f;

	Node* m_rootNode;
	int m_scrollX;
	int m_scrollSpeedX;
	bool m_isOutOfSelect;


protected:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void LateDraw() override;

public:
	SceneStageSelect() :
		m_rootNode(nullptr),
		m_scrollX(0),
		m_scrollSpeedX(0),
		m_isOutOfSelect(false)
	{}

	int GetMaxShowPlanetAmount()
	{
		return MaxShowPlanetAmount;
	}

	int GetScrollX() const
	{
		return m_scrollX;
	}

};
