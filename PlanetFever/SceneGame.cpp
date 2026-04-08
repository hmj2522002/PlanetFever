#include "SceneGame.h"
#include "Actor2D.h"
#include "Planet.h"
#include "MeteorGenerator.h"
#include "Input.h"
#include "SceneResult.h"
#include "Rocket.h"
#include "GameInfo.h"
#include "TimeLeftUI.h"
#include "Fade.h"
#include "Bgm.h"

void SceneGame::Initialize()
{
	// 前回挑戦したステージの情報を初期化
	GameInfo::GetInstance()->Reset();

	m_rootNode = new Node();

	m_rootNode->AddChild(new Actor2D("Resource/BG.png"));

	Planet* planet = new Planet();
	m_rootNode->AddChild(planet);

	Rocket* rocket = new Rocket();
	m_rootNode->AddChild(rocket);

	MeteorGenerator* meteorGenerator = new MeteorGenerator();
	m_rootNode->AddChild(meteorGenerator);

	TimeLeftUI* timeLeftUI = new TimeLeftUI();
	m_rootNode->AddChild(timeLeftUI);

	m_largeText = new LargeText(LargeText::Text::Ready);
	m_rootNode->AddChild(m_largeText);

	Bgm::GetInstance()->ChangeBgm(Bgm::BgmType::Main);

	m_defaultTimeLeft = GameInfo::TimeFrameLeft;
}

void SceneGame::Finalize()
{
	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}
}

void SceneGame::Update()
{
	m_rootNode->TreeUpdate();

	GameInfo::GetInstance()->Update();

	m_timeLeft = GameInfo::GetInstance()->GetTimeLeft();
	m_isTimeUp = GameInfo::GetInstance()->IsTimeUp();
	m_inGame = GameInfo::GetInstance()->InGame();

	if (m_isTimeUp)
	{
		m_endDurationTimeFrame--;
	}

	// 中央のテキスト表示
	if (m_inGame)
	{
		m_largeText->ChangeText(LargeText::Text::Start);
	}
	else if (m_isTimeUp)
	{
		m_largeText->ChangeText(LargeText::Text::Finish);
	}

	// 一定時間が経過したらリザルト画面へ
	if (m_endDurationTimeFrame <= 0 && !Fade::GetInstance()->IsFade())
	{
		SceneManager::GetInstance()->LoadScene(new SceneResult());
	}
}

void SceneGame::Draw()
{
	m_rootNode->TreeDraw();
}

void SceneGame::LateDraw()
{
	m_rootNode->TreeLateDraw();

	if (m_defaultTimeLeft - HideTextDuration < m_timeLeft ||
		m_isTimeUp)
	{
		m_largeText->UIDraw();
	}
}
