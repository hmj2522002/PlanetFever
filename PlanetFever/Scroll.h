#pragma once
#include "Vector2.h"
#include "Screen.h"
#include <list>

class Actor2D;

class Scroll
{
private:
	static constexpr float ScrollChaseSpeed = 0.5f;
	static constexpr float CameraScaleChangeSpeed = 1;
	static constexpr float MaxScale = 1.0f;
	static constexpr float MinScale = 0.6f;
	static constexpr float MaxCameraDist = 800.0f;
	static constexpr bool IsHorizontalScreen = Screen::Height < Screen::Width;
	static constexpr int ShakeSpanFrame = 4;

	// オブジェクトが画面端で途切れないように少し縮小する
	static constexpr float BaseScreenDist = IsHorizontalScreen ?
		Screen::Height * 0.6f : Screen::Width * 0.6f;


	Vector2 drawPosition;
	Vector2 position;
	Vector2 shakeOffset;
	Vector2 drawShakeOffset;
	float topObject;
	float bottomObject;
	float leftObject;
	float rightObject;
	float drawCameraScale;
	float cameraScale;
	float shakeRange;
	int shakeTime;
	int prevShakeTime;

	std::list<Actor2D*> m_actorList;

public:
	static constexpr Vector2 DefaultScrollPosition = (Screen::Center);

	Scroll() :
		drawPosition(DefaultScrollPosition),
		position(DefaultScrollPosition),
		topObject(DefaultScrollPosition.y),
		bottomObject(DefaultScrollPosition.y),
		leftObject(DefaultScrollPosition.x),
		rightObject(DefaultScrollPosition.x),
		drawCameraScale(1.0f),
		cameraScale(1.0f),
		shakeTime(0),
		shakeRange(0),
		prevShakeTime(0)
	{ }

	void Update();
	void Draw();

	// シングルトン
	static Scroll* GetInstance()
	{
		static Scroll instance;
		return &instance;
	}

	// スクロール位置を瞬時に指定位置に移動
	void SetPosition(Vector2 pos)
	{
		ChangePosition(pos);
		drawPosition = pos;
	}

	// スクロール位置をゆっくりと指定位置まで移動
	void ChangePosition(Vector2 pos)
	{
		position = pos;
	}

	Vector2 GetPosition() const
	{
		return drawPosition;
	}

	// 描画範囲を瞬時に指定範囲に変更
	void SetCameraScale(float scale)
	{
		drawCameraScale = scale;
		ChangeCameraScale(scale);
	}

	// 描画範囲をゆっくりと指定範囲まで変更
	void ChangeCameraScale(float scale)
	{
		cameraScale = scale;
	}

	float GetCameraScale() const
	{
		return drawCameraScale;
	}

	// 画面拡縮に対応させる
	void Register(Actor2D* actor)
	{
		m_actorList.push_back(actor);
	}

	// 画面拡縮非対応にさせる
	void Remove(Actor2D* actor)
	{
		m_actorList.remove(actor);
	}

	Vector2 GetScrollAndDefaultPosDiff() const
	{
		return DefaultScrollPosition - drawPosition;
	}

	// 画面を揺らす時間を指定
	void ScreenShake(int timeFrame = 15, float range = 15)
	{
		shakeTime = timeFrame;
		shakeRange = range;
	}

	Vector2 GetScreenShake() const
	{
		return drawShakeOffset;
	}
};
