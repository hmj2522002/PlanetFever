#include "SceneStageSelect.h"
#include "Actor2D.h"
#include "StageSelectPlanet.h"
#include "Input.h"
#include "SceneGame.h"
#include "Scroll.h"
#include "ScoreUI.h"
#include "GameInfo.h"
#include "Bgm.h"

void SceneStageSelect::Initialize()
{
	m_rootNode = new Node();

	m_rootNode->AddChild(new Actor2D("Resource/BG.png"));

	StageSelectPlanet* stageSelectPlanet[MaxShowPlanetAmount]{};
	for (int i = 0; i < MaxShowPlanetAmount; i++)
	{
		stageSelectPlanet[i] = new StageSelectPlanet(i, this);
		m_rootNode->AddChild(stageSelectPlanet[i]);
	}

	m_largeText = new LargeText(
		LargeText::Text::ClickThePlanet,
		Screen::Center + TextOffset,
		true
	);
	m_rootNode->AddChild(m_largeText);

	m_rootNode->AddChild(new ScoreUI());

	// スクロール位置、拡縮調整
	Scroll::GetInstance()->SetPosition(Scroll::DefaultScrollPosition);
	Scroll::GetInstance()->SetCameraScale(0.3f);
	Scroll::GetInstance()->ChangeCameraScale(1.0f);

	// 直前のゲーム内情報をリセットさせる
	GameInfo::GetInstance()->Reset();

	// 横スクロールを前回挑戦したステージに合わせる
	m_scrollX = static_cast<int>(
		SaveData::GetInstance()->GetStage())
		* StageSelectPlanet::PlanetInterval;

	m_prevNearestPlanetNum = static_cast<int>(
		SaveData::GetInstance()->GetStage());

	Bgm::GetInstance()->ChangeBgm(Bgm::BgmType::Rest);

	m_seSelect = LoadSoundMem("Sounds/se_count.mp3");
}

void SceneStageSelect::Finalize()
{
	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}
}

void SceneStageSelect::Update()
{
	// 選択できる惑星の範囲外か
	m_isOutOfSelect = m_scrollX <= 0 ||
		StageSelectPlanet::PlanetInterval * (PlanetInfo::MaxStage - 1) <= m_scrollX;

	float scrollSpeed = m_isOutOfSelect ? ScrollSpeedDown : 1.0f;

	int planetInterval = StageSelectPlanet::PlanetInterval;

	int nearestPlanetNum = std::round(m_scrollX / static_cast<float>(planetInterval));
	nearestPlanetNum = Math::Clamp(nearestPlanetNum, 0, PlanetInfo::MaxStage - 1);

	if (m_prevNearestPlanetNum != nearestPlanetNum)
	{
		PlaySoundMem(m_seSelect, DX_PLAYTYPE_BACK);
	}

	m_prevNearestPlanetNum = nearestPlanetNum;

	if (Mouse::IsDown(MOUSE_INPUT_LEFT))
	{
		m_isScrollControll = false;
	}

	if (Mouse::IsPress(MOUSE_INPUT_LEFT))
	{
		m_scrollSpeedX = static_cast<int>(Mouse::GetPointDelta().x) * -1;
		
		m_scrollSpeedX *= scrollSpeed;

		if (0 < Math::Abs(m_scrollSpeedX))
		{	
			// ボタン判定とスクロール操作が重複しないようにフラグを立てる
			m_isScrollControll = true;
		}
	}
	else
	{
		m_scrollSpeedX = Math::Clamp(m_scrollSpeedX, static_cast<int>(-MaxScrollSpeed * scrollSpeed), static_cast<int>(MaxScrollSpeed * scrollSpeed));

		// マウス操作がないときは減速させる
		if (0 < m_scrollSpeedX)
		{
			m_scrollSpeedX--;

			// 減速中に方向が逆になったら０に戻す
			if (m_scrollSpeedX < 0) m_scrollSpeedX = 0;
		}
		// 反対側も同じ
		if (m_scrollSpeedX < 0)
		{
			m_scrollSpeedX++;

			if (0 < m_scrollSpeedX) m_scrollSpeedX = 0;
		}

		// 慣性がなくなったら自動補正する
		if (Math::Abs(m_scrollSpeedX) <= 1)
		{
			int checkPlanetPos = nearestPlanetNum * planetInterval;

			// 直近の惑星に向かってスクロールする
			if (m_scrollX < checkPlanetPos)
			{
				m_scrollX += FixScrollSpeed;
				if (checkPlanetPos < m_scrollX)
				{
					// 通り過ぎたら目標の惑星に合わせる
					m_scrollX = checkPlanetPos;
				}
			}
			// 逆も然り
			if (checkPlanetPos < m_scrollX)
			{
				m_scrollX -= FixScrollSpeed;
				if (m_scrollX < checkPlanetPos)
				{
					m_scrollX = checkPlanetPos;
				}
			}
		}
	}

	m_scrollX += m_scrollSpeedX;

	m_rootNode->TreeUpdate();
}

void SceneStageSelect::Draw()
{
	m_rootNode->TreeDraw();
}

void SceneStageSelect::LateDraw()
{
	m_rootNode->TreeLateDraw();

	m_largeText->UIDraw();
}
