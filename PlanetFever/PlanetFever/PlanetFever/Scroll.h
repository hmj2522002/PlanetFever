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
	static constexpr float MinScale = 0.4f;
	static constexpr float MaxCameraDist = 1500.0f;
	static constexpr bool IsHorizontalScreen = Screen::Height < Screen::Width;

	// オブジェクトが画面端で途切れないように少し縮小する
	static constexpr float BaseScreenDist = IsHorizontalScreen ?
		Screen::Height * 0.6f : Screen::Width * 0.6f;


	Vector2 drawPosition;
	Vector2 position;
	float topObject;
	float bottomObject;
	float leftObject;
	float rightObject;
	float drawCameraScale;
	float cameraScale;

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
		cameraScale(1.0f)
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
};
