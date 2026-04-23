#include "Animation2D.h"
#include "Transform2D.h"
#include "Screen.h"
#include "Node.h"
#include "GameConfig.h"

Animation2D::Animation2D(const char* handle, int tiles, int speed, bool loopFlag) :
	m_animeTime(0),
	m_handle(handle),
	m_id(0),
	m_animeNum(0),
	m_animeType(0),
	m_prevAnimeType(0),
	m_tiles(tiles),
	m_speed(speed),
	m_loopFlag(loopFlag),
	m_isFlipX(false),
	m_isLooped(false),
	m_isDraw(true),
	m_timeFrame(0),
	m_brightness(255),
	m_glidSize(Vector2())
{
	m_id = LoadGraph(m_handle);
}

void Animation2D::Load()
{
	if (m_glidSize == Vector2(0, 0))
	{
		GetGraphSizeF(m_id, &m_glidSize.x, &m_glidSize.y);
	}
}

void Animation2D::Release()
{

}

void Animation2D::Update()
{
	if (!m_loopFlag && m_isLooped || m_tiles <= 1)
	{
		m_animeTime = 0;
		m_animeNum = 0;
		return;
	}

	m_timeFrame++;
	m_isLooped = false;
	
	m_animeTime = m_timeFrame * (m_speed / static_cast<float>(GameConfig::FPS));

	if (m_tiles <= m_animeTime && 1 < m_tiles)
	{
		m_isLooped = true;

		if (!m_loopFlag)
		{
			// ÅIƒtƒŒ[ƒ€‚ÅŽ~‚ß‚é
			m_animeNum = m_tiles - 1;
			return;
		}

		m_animeTime = 0;
		m_timeFrame = 0;
	}

	m_animeNum = static_cast<int>(m_animeTime);

	if (m_animeType != m_prevAnimeType)
	{
		m_animeTime = 0;
		m_timeFrame = 0;
	}

	m_prevAnimeType = m_animeType;
}

void Animation2D::Draw(const Transform2D& transform, Layer layer)
{
	this->MainDraw(transform, layer);
}

void Animation2D::LateDraw(const Transform2D& transform, Layer layer)
{
	this->MainDraw(transform, layer);
}

void Animation2D::MainDraw(const Transform2D& transform, Layer layer) const
{
	if (!m_isDraw) return;

	Vector2 scrollPos;
	float cameraScale;

	scrollPos = layer == Layer::Object ?
		Scroll::GetInstance()->GetPosition() :
		Vector2();

	cameraScale = layer == Layer::Object ?
		Scroll::GetInstance()->GetCameraScale() :
		1.0f;

	Vector2 drawPos = Vector2(
		((transform.position.x - scrollPos.x + (Screen::Width / 2.0f / cameraScale)) * cameraScale),
		((transform.position.y - scrollPos.y + (Screen::Height / 2.0f / cameraScale)) * cameraScale));

	Vector2 drawShake = Scroll::GetInstance()->GetScreenShake();

	SetDrawBright(m_brightness, m_brightness, m_brightness);

	DrawRectRotaGraph(
		static_cast<int>(drawPos.x + static_cast<float>(drawShake.x * cameraScale)),
		static_cast<int>(drawPos.y + static_cast<float>(drawShake.y * cameraScale)),
		static_cast<int>(m_glidSize.x) * m_animeNum,
		static_cast<int>(m_glidSize.y) * m_animeType,
		static_cast<int>(m_glidSize.x),
		static_cast<int>(m_glidSize.y),
		transform.scale * cameraScale,
		transform.angle,
		m_id,
		true,
		m_isFlipX
	);
	SetDrawBright(255, 255, 255);

}
