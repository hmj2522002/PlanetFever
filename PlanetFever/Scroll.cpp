#include "Scroll.h"
#include "GameConfig.h"
#include "Input.h"
#include "Actor2D.h"
#include "Math.hpp"

void Scroll::Update()
{
	float top = DefaultScrollPosition.y;
	float bottom = DefaultScrollPosition.y;
	float left = DefaultScrollPosition.x;
	float right = DefaultScrollPosition.x;

	// 登録されているオブジェクトの中から最も端にあるオブジェクトを４か所選別
	for (auto actor : m_actorList)
	{
		if (actor->GetPosition().y <= top)
		{
			top = Math::Clamp(
				actor->GetPosition().y,
				DefaultScrollPosition.y - MaxCameraDist * cameraScale,
				DefaultScrollPosition.y
			);
		}

		if (bottom <= actor->GetPosition().y)
		{
			bottom = Math::Clamp(
				actor->GetPosition().y,
				DefaultScrollPosition.y,
				DefaultScrollPosition.y + MaxCameraDist * cameraScale
			);
		}

		if (actor->GetPosition().x <= left)
		{
			left = Math::Clamp(
				actor->GetPosition().x,
				DefaultScrollPosition.x - MaxCameraDist * cameraScale,
				DefaultScrollPosition.x
			);
		}

		if (right <= actor->GetPosition().x)
		{
			right = Math::Clamp(
				actor->GetPosition().x,
				DefaultScrollPosition.x,
				DefaultScrollPosition.x + MaxCameraDist * cameraScale
			);
		}
	}

	float width = right - left;
	float height = bottom - top;

	topObject = top;
	bottomObject = bottom;
	leftObject = left;
	rightObject = right;

	// 選択した４か所の座標を使って仮の矩形を作る
	Vector2 topLeft = Vector2(left, top);
	Vector2 topRight = Vector2(right, top);
	Vector2 bottomLeft = Vector2(left, bottom);
	Vector2 bottomRight = Vector2(right, bottom);

	float dist = max(width, height);
	Vector2 center = Vector2(
		(left + right) * 0.5f,
		(top + bottom) * 0.5f
	);

	position = Vector2(
		center.x - DefaultScrollPosition.x * cameraScale + DefaultScrollPosition.x * cameraScale,
		center.y - DefaultScrollPosition.y * cameraScale + DefaultScrollPosition.y * cameraScale
	);

	if (dist <= 0.0001f)
	{
		// ０除算回避
		dist = 1.0f;
	}

	if (0 < shakeTime)
	{
		prevShakeTime = shakeTime;
		shakeTime--;

		if (prevShakeTime < shakeTime ||
			shakeTime % ShakeSpanFrame == 0)
		{
			float x = static_cast<float>((rand() % static_cast<int>(shakeRange) * 2) - static_cast<int>(shakeRange));
			float y = static_cast<float>((rand() % static_cast<int>(shakeRange) * 2) - static_cast<int>(shakeRange));
		
			shakeOffset = Vector2(x, y);
		}
	}
	else
	{
		if (shakeTime != prevShakeTime)
		{
			shakeOffset = Vector2(0, 0);
		}
		prevShakeTime = shakeTime;
	}

	drawShakeOffset = (shakeOffset + drawShakeOffset) / 2.0f;

	cameraScale = (BaseScreenDist / (dist / 1.0f));
	cameraScale = Math::Clamp(cameraScale, MinScale, MaxScale);

	drawPosition += (position - drawPosition) / GameConfig::FPS * ScrollChaseSpeed;
	drawCameraScale += (cameraScale - drawCameraScale) / GameConfig::FPS * CameraScaleChangeSpeed;

}

void Scroll::Draw()
{

}
