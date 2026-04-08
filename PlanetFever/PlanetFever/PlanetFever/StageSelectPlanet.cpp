#include "StageSelectPlanet.h"
#include "Screen.h"
#include "PlanetInfo.h"

StageSelectPlanet::StageSelectPlanet(int imageNum, SceneStageSelect* sceneStageSelect) :
	Actor2D("Resource/planets.png", Tag::None, Layer::Object, m_transform), 
	m_sceneStageSelect(sceneStageSelect),
	m_scrollX(0),
	m_imageNum(imageNum),
	m_id(0),
	m_maxShowPlanet(0),
	m_planetPos(0),
	dummy(0)
{
	m_sprite->SetGlidSize(GlidSize);
	m_button = new Button(this, 100);
}

void StageSelectPlanet::Load()
{
	m_maxShowPlanet = m_sceneStageSelect->GetMaxShowPlanetAmount();

	m_sprite->SetAnimeType(0);

	Actor2D::Load();
}

void StageSelectPlanet::Release()
{
	Actor2D::Release();
}

void StageSelectPlanet::Update()
{
	if (CheckPlanetLoop(m_imageNum) == ScrollOut::Left)
	{
		dummy++;
		m_imageNum += m_maxShowPlanet;
	}
	if (CheckPlanetLoop(m_imageNum) == ScrollOut::Right)
	{
		dummy--;
		m_imageNum -= m_maxShowPlanet;
	}

	if (m_button->IsPress()) Release();

	m_scrollX = m_sceneStageSelect->GetScrollX();

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		m_scrollX += 10;

	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		m_scrollX -= 10;
	}

	m_planetPos = PlanetInterval * m_imageNum;

	m_transform.scale = 1.0f - Math::Abs(m_scrollX - m_planetPos) 
		/ static_cast<float>(Screen::Width) 
		/ ShowWidthMagnification;
	
	m_transform.position =
		Screen::Center +
		Vector2(m_scrollX * -1 + m_planetPos, 0) * m_transform.scale * 1.5f;


	Actor2D::Update();
}

void StageSelectPlanet::Draw()
{
	DrawFormatString(0, 40 + 20 * m_imageNum, GetColor(0, 255, 255),"StageSelectPlanet %d", m_planetPos);
	DrawFormatString(300, 0, GetColor(122, 255, 255), "StageSelectPlanet %d", m_scrollX);



	if (MaxShowPlanetWidth / 2.0f < Math::Abs(m_planetPos - m_scrollX))
	{
		return;
	}

	Actor2D::Draw();
}

void StageSelectPlanet::LateDraw()
{
	Draw();
}

StageSelectPlanet::ScrollOut StageSelectPlanet::CheckPlanetLoop(int planetNum) const
{
	int planetPos = PlanetInterval * planetNum;

	// 画面左に惑星が移動した
	if (planetPos < m_scrollX - MaxShowPlanetWidth / 2.0f)
	{
		// 位置が最大ステージ数より大きくなりそうならそのまま
		if (PlanetInfo::MaxStage - 1 < planetNum + m_maxShowPlanet)
		{
			return ScrollOut::None;
		}

		return ScrollOut::Left;
	}

	// 画面右に惑星が移動した
	if (m_scrollX + MaxShowPlanetWidth / 2.0f < planetPos)
	{
		// 位置が０より小さくなりそうならそのまま
		if (planetNum - m_maxShowPlanet < 0)
		{
			return ScrollOut::None;
		}

		return ScrollOut::Right;
	}

	// 両端に移動していないのでそのまま
	return ScrollOut::None;
}

