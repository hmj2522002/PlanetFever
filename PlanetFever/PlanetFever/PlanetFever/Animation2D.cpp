#include "Animation2D.h"
#include "Transform2D.h"
#include "Screen.h"
#include "Node.h"
#include "GameConfig.h"

Animation2D::Animation2D(const char* handle, int tiles, int speed, bool loopFlag) :
	m_handle(handle),
	m_id(0),
	m_animeNum(0),
	m_animeType(0),
	m_prevAnimeType(0),
	m_tiles(tiles),
	m_speed(speed),
	m_loopFlag(loopFlag),
	m_timeFrame(0),
	m_glidSize(Vector2())
{
	m_id = LoadGraph(m_handle);
}
//Animation2D::Animation2D(const char* handle) :
//	Animation2D(handle, 1, 0, true)
//{
//}

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
	if (m_tiles <= 1) return;

	m_timeFrame++;
	
	float animeTime = m_timeFrame * static_cast<float>(m_speed) / GameConfig::FPS;

	if (m_tiles <= animeTime)
	{
		animeTime = 0;
		m_timeFrame = 0;
	}

	m_animeNum = static_cast<int>(animeTime);
}

void Animation2D::Draw(const Transform2D& transform, Layer layer) const
{
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

	
	DrawRectRotaGraph(
		static_cast<int>(drawPos.x),
		static_cast<int>(drawPos.y),
		static_cast<int>(m_glidSize.x) * m_animeNum,
		static_cast<int>(m_glidSize.y) * m_animeType,
		static_cast<int>(m_glidSize.x),
		static_cast<int>(m_glidSize.y),
		transform.scale * cameraScale,
		transform.angle,
		m_id,
		true
	);
}

void Animation2D::LateDraw(const Transform2D& transform, Layer layer) const
{
	Animation2D::Draw(transform, layer);
}
