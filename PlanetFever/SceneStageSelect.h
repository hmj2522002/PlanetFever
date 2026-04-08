#pragma once
#include "SceneBase.h"
#include "Node.h"
#include "Vector2.h"
#include "LargeText.h"
#include "SmallText.h"
#include "DrawNumber.h"

class SceneStageSelect : public SceneBase
{
private:
	static constexpr Vector2 TextOffset = Vector2(0, -200);
	static constexpr int MaxShowPlanetAmount = 5;
	static constexpr int MaxScrollSpeed = 60;
	static constexpr int FixScrollSpeed = 8;
	static constexpr float ScrollSpeedDown = 0.25f;

	Node* m_rootNode;
	LargeText* m_largeText;
	int m_scrollX;
	int m_scrollSpeedX;
	int m_seSelect;
	int m_nearestPlanetNum;
	int m_prevNearestPlanetNum;
	bool m_isOutOfSelect;
	bool m_isScrollControll;

protected:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void LateDraw() override;

public:
	SceneStageSelect() :
		m_rootNode(nullptr),
		m_largeText(nullptr),
		m_scrollX(0),
		m_scrollSpeedX(0),
		m_seSelect(0),
		m_nearestPlanetNum(0),
		m_prevNearestPlanetNum(0),
		m_isOutOfSelect(false),
		m_isScrollControll(false)
	{}

	int GetMaxShowPlanetAmount()
	{
		return MaxShowPlanetAmount;
	}

	int GetScrollX() const
	{
		return m_scrollX;
	}

	bool GetIsScrolling() const
	{
		return m_isScrollControll;
	}

};
