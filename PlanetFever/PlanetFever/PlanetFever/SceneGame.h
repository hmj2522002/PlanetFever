#pragma once
#include "SceneBase.h"
#include "Node.h"

class SceneGame : public SceneBase
{
private:
	static constexpr int EndDurationTimeFrame = 150;

	Node* m_rootNode;
	int m_endDurationTimeFrame;

protected:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void LateDraw() override;

public:
	SceneGame() :
		m_rootNode(nullptr),
		m_endDurationTimeFrame(EndDurationTimeFrame)
	{}

};
