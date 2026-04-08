#pragma once
#include "Actor2D.h"
#include "Animation2D.h"
#include "SceneStageSelect.h"
#include "Screen.h"
#include "Button.h"

class StageSelectPlanet : public Actor2D
{
public:
	static constexpr int PlanetInterval = 250;
	static constexpr float ShowWidthMagnification = 1.7f;	// 惑星の間隔の倍率

private:
	static constexpr Vector2 GlidSize = Vector2(250, 250);
	static constexpr int MaxShowPlanetWidth = Screen::Width + static_cast<int>(GlidSize.x);

	// 惑星ごとのテクスチャ
	const Animation2D PlanetTextures[1] =
	{
		Animation2D("Resource/planets.png")
	};

	SceneStageSelect* m_sceneStageSelect;
	Button* m_button;
	int m_scrollX;
	int m_imageNum;
	int m_id;
	int m_maxShowPlanet;
	int m_planetPos;
	int dummy;

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
