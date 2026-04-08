#pragma once
#include "SceneBase.h"
#include "Node.h"
#include "Vector2.h"

class SceneTitle : public SceneBase
{
private:
	static constexpr Vector2 TextOffset = Vector2(0, -80);

	Node* m_rootNode;

protected:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void LateDraw() override;

public:
	SceneTitle();

};
