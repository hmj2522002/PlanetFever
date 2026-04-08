#include "SceneStageSelect.h"
#include "Actor2D.h"
#include "StageSelectPlanet.h"
#include "Input.h"
#include "SceneGame.h"
#include "Scroll.h"
#include "LargeText.h"
#include "ScoreUI.h"
#include "GameInfo.h"

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

	m_rootNode->AddChild(new LargeText(
		LargeText::Text::ClickThePlanet,
		Screen::Center + TextOffset,
		true
	));

	m_rootNode->AddChild(new ScoreUI());

	// スクロール位置、拡縮調整
	Scroll::GetInstance()->SetPosition(Scroll::DefaultScrollPosition);
	Scroll::GetInstance()->SetCameraScale(0.3f);
	Scroll::GetInstance()->ChangeCameraScale(1.0f);

	// 直前のゲーム内情報をリセットさせる
	GameInfo::GetInstance()->Reset();

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
	m_isOutOfSelect = m_scrollX <= 0 ||
		StageSelectPlanet::PlanetInterval * (PlanetInfo::MaxStage - 1) <= m_scrollX;

	float scrollSpeed = m_isOutOfSelect ? ScrollSpeedDown : 1.0f;

	if (Mouse::IsAnyPress())
	{
		m_scrollSpeedX = static_cast<int>(Mouse::GetPointDelta().x) * -1;
		
		m_scrollSpeedX *= scrollSpeed;
		
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

		int planetInterval = StageSelectPlanet::PlanetInterval;

		// 慣性がなくなったら自動補正する
		if (Math::Abs(m_scrollSpeedX) <= 1)
		{
			int nearestPlanetNum = std::round(m_scrollX / static_cast<float>(planetInterval));
			nearestPlanetNum = Math::Clamp(nearestPlanetNum, 0, PlanetInfo::MaxStage - 1);

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

	if (Keyboard::IsDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance()->LoadScene(new SceneGame());
	}

	m_rootNode->TreeUpdate();
}

void SceneStageSelect::Draw()
{
	m_rootNode->TreeDraw();

	DrawFormatString(
		0, 0,
		GetColor(255, 255, 255),
		"SceneStageSelect : %d", m_scrollX
	);
}

void SceneStageSelect::LateDraw()
{
	m_rootNode->TreeLateDraw();
}
