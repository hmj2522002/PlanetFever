#pragma once
#include "SceneBase.h"
#include "Node.h"
#include "LargeText.h"

class SceneGame : public SceneBase
{
private:
	static constexpr int EndDurationTimeFrame = 150;
	static constexpr int HideTextDuration = 60;

	Node* m_rootNode;
	LargeText* m_largeText;
	int m_endDurationTimeFrame;
	int m_timeLeft;
	int m_defaultTimeLeft;
	bool m_isTimeUp;
	bool m_inGame;

protected:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void LateDraw() override;

public:
	SceneGame() :
		m_rootNode(nullptr),
		m_largeText(nullptr),
		m_endDurationTimeFrame(EndDurationTimeFrame),
		m_timeLeft(0),
		m_defaultTimeLeft(0),
		m_isTimeUp(false),
		m_inGame(false)
	{}

};
