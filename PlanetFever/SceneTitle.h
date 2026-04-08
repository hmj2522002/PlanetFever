#pragma once
#include "SceneBase.h"
#include "Node.h"
#include "Vector2.h"
#include "LargeText.h"

class SceneTitle : public SceneBase
{
private:
	static constexpr Vector2 TextOffset = Vector2(0, -80);
	static constexpr Vector2 LogoOffset = Vector2(0, -60);

	Node* m_rootNode;
	LargeText* m_largeText;
	int m_seNext;

protected:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void LateDraw() override;

public:
	SceneTitle();

};
