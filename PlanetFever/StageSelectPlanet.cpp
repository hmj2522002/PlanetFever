#include "StageSelectPlanet.h"
#include "Screen.h"
#include "PlanetInfo.h"
#include "SaveData.h"
#include "SceneManager.h"
#include "SceneGame.h"

StageSelectPlanet::StageSelectPlanet(int imageNum, SceneStageSelect* sceneStageSelect) :
	Actor2D("Resource/planets.png", Tag::None, Layer::Object, m_transform), 
	m_sceneStageSelect(sceneStageSelect),
	m_button(nullptr),
	m_smallText(nullptr),
	m_drawNumber(nullptr),
	m_scrollX(0),
	m_imageNum(imageNum),
	m_prevImageNum(-1),
	m_id(0),
	m_maxShowPlanet(0),
	m_planetPos(0),
	m_seNext(0),
	m_isScrollControll(false),
	m_canSelectThis(false)
{
	m_sprite->SetGlidSize(GlidSize);
	m_button = new Button(this, 100);
	m_smallText = new SmallText(SmallText::Text::NeedScore);
	m_drawNumber = new DrawNumber();
}

void StageSelectPlanet::Load()
{
	m_maxShowPlanet = m_sceneStageSelect->GetMaxShowPlanetAmount();

	m_seNext = LoadSoundMem("Sounds/se_next.mp3");

	Actor2D::Load();
}

void StageSelectPlanet::Release()
{
	DeleteSoundMem(m_seNext);


	delete m_smallText;
	delete m_drawNumber;
	m_smallText = nullptr;
	m_drawNumber = nullptr;

	Actor2D::Release();
}

void StageSelectPlanet::Update()
{
	m_button->Update();

	if (CheckPlanetLoop(m_imageNum) == ScrollOut::Left)
	{
		m_imageNum += m_maxShowPlanet;
	}
	if (CheckPlanetLoop(m_imageNum) == ScrollOut::Right)
	{
		m_imageNum -= m_maxShowPlanet;
	}

	// 前フレームとimageNumが同じではなかったら本来あるべき見た目に変える
	if (m_imageNum != m_prevImageNum)
	{
		m_sprite->SetAnimeType(m_imageNum);
		
		m_canSelectThis = PlanetInfo::PlanetCosts[m_imageNum] <= SaveData::GetInstance()->GetScore();

		if (m_canSelectThis)
		{
			m_sprite->SetBrightness();
		}
		else
		{
			m_sprite->SetBrightness(128);
		}
	}

	if (m_button->IsDownToUp() 
		&& !m_sceneStageSelect->GetIsScrolling() 
		&& m_canSelectThis
		)
	{
		// 惑星がクリックされたので、セーブデータに最後にプレイしたステージの情報を上書きする
		SaveData::GetInstance()->SetStage(static_cast<PlanetInfo::PlanetName>(m_imageNum));
		SceneManager::GetInstance()->LoadScene(new SceneGame());
		PlaySoundMem(m_seNext, DX_PLAYTYPE_BACK);
	}

	m_scrollX = m_sceneStageSelect->GetScrollX();

	m_planetPos = PlanetInterval * m_imageNum;

	m_transform.scale = 1.0f - Math::Abs(m_scrollX - m_planetPos) 
		/ static_cast<float>(Screen::Width) 
		/ ShowWidthMagnification;
	
	m_transform.position =
		Screen::Center +
		Vector2(m_scrollX * -1 + m_planetPos, 0) * m_transform.scale * 1.5f;

	m_prevImageNum = m_imageNum;

	Actor2D::Update();
}

void StageSelectPlanet::Draw()
{
	if (MaxShowPlanetWidth / 2.0f < Math::Abs(m_planetPos - m_scrollX))
	{
		return;
	}

	Actor2D::Draw();

	if (m_canSelectThis)
	{
		if (!SaveData::GetInstance()->GetPlayCount(static_cast<PlanetInfo::PlanetName>(m_imageNum)))
		{
			m_smallText->ChangeText(SmallText::Text::New);
			m_smallText->Draw(m_transform.position + TextOffset, UIsize);
		}
	}
	else
	{
		m_smallText->ChangeText(SmallText::Text::NeedScore);
		m_smallText->Draw(m_transform.position + TextOffset, UIsize);
		m_drawNumber->Draw(PlanetInfo::PlanetCosts[m_imageNum], m_transform.position + NumberOffset, UIsize);
	}
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

