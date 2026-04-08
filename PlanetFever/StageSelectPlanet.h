#pragma once
#include "Actor2D.h"
#include "Animation2D.h"
#include "SceneStageSelect.h"
#include "Screen.h"
#include "Button.h"
#include "SmallText.h"
#include "DrawNumber.h"

class StageSelectPlanet : public Actor2D
{
public:
	static constexpr Vector2 TextOffset = Vector2(0, 120);
	static constexpr Vector2 NumberOffset = Vector2(0, 160);
	static constexpr float ShowWidthMagnification = 1.7f;	// 惑星の間隔の倍率
	static constexpr float UIsize = 0.75f;
	static constexpr int PlanetInterval = 250;

private:
	static constexpr Vector2 GlidSize = Vector2(250, 250);
	static constexpr int MaxShowPlanetWidth = Screen::Width + static_cast<int>(GlidSize.x);	// 画面中央からの表示域
	static constexpr int CannotSelectBrightness = 64;	// 惑星が選択できないときの明るさ（基準は255）

	SceneStageSelect* m_sceneStageSelect;
	Button* m_button;
	SmallText* m_smallText;
	DrawNumber* m_drawNumber;
	int m_scrollX;
	int m_imageNum;
	int m_prevImageNum;
	int m_id;
	int m_maxShowPlanet;
	int m_planetPos;
	int m_seNext;
	bool m_isScrollControll;
	bool m_canSelectThis;

	// 画面外に行ったかを判別する用
	enum class ScrollOut
	{
		None,	// 画面内
		Right,	// 右側に行った
		Left	// 左側に行った
	};

	// 惑星が画面外に行ったかの処理
	ScrollOut CheckPlanetLoop(int planetNum) const;


protected:
	virtual void Load() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void LateDraw() override;

public:
	StageSelectPlanet(int imageNum, SceneStageSelect* sceneStageSelect);

	int GetPlanetInterval()
	{
		return PlanetInterval;
	}
};
