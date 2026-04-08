#include "SceneGame.h"
#include "Actor2D.h"
#include "Planet.h"
#include "Player.h"
#include "MeteorGenerator.h"
#include "Input.h"
#include "SceneResult.h"
#include "Rocket.h"
#include "GameInfo.h"
#include "TimeLeftUI.h"

void SceneGame::Initialize()
{
	m_rootNode = new Node();

	m_rootNode->AddChild(new Actor2D("Resource/BG.png"));

	Planet* planet = new Planet();
	m_rootNode->AddChild(planet);

	Rocket* rocket = new Rocket();
	m_rootNode->AddChild(rocket);

	Player* player = new Player();
	m_rootNode->AddChild(player);

	MeteorGenerator* meteorGenerator = new MeteorGenerator();
	m_rootNode->AddChild(meteorGenerator);

	TimeLeftUI* timeLeftUI = new TimeLeftUI();
	m_rootNode->AddChild(timeLeftUI);
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

	if (GameInfo::GetInstance()->IsTimeUp())
	{
		m_endDurationTimeFrame--;
	}

	if (Keyboard::IsDown(KEY_INPUT_0) || m_endDurationTimeFrame <= 0)
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
}
