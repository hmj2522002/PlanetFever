#pragma once
#include "SceneBase.h"
#include "Node.h"
#include "Vector2.h"
#include "ResultUI.h"
#include "SceneResult.h"
#include "LargeText.h"
#include <list>

class SceneResult : public SceneBase
{
private:
	static constexpr Vector2 BackTextOffset = Vector2(0, -80);
	static constexpr Vector2 ResultTextOffset = Vector2(0, 80);
	static constexpr Vector2 FinalResultOffset = Vector2(0, -200);
	static constexpr int TopResultUIpos = Screen::Top + 250;
	static constexpr int ResultUIinterval = 70;

	Node* m_rootNode;
	LargeText* m_backText;
	LargeText* m_resultText;
	std::list<ResultUI*> m_resultUIList;
	int m_seNext;

protected:
	virtual void Initialize() override;
	virtual void Finalize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void LateDraw() override;

public:
	SceneResult();

};
