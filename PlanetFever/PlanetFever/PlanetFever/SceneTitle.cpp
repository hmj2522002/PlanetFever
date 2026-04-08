#include "SceneTitle.h"
#include "Animation2D.h"
#include "SceneStageSelect.h"
#include "Input.h"
#include "LargeText.h"

SceneTitle::SceneTitle()
{
	m_rootNode = new Node();

	m_rootNode->AddChild(new Actor2D("Resource/BG.png"));

	m_rootNode->AddChild(new LargeText(
		LargeText::Text::ClickToStart,
		Vector2(Screen::Width / 2.0f, Screen::Height) + TextOffset,
		true
	));
}

void SceneTitle::Initialize()
{
	
}

void SceneTitle::Finalize()
{
	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		m_rootNode = nullptr;
		delete m_rootNode;
	}
}

void SceneTitle::Update()
{
	if (Mouse::IsAnyPress())
	{
		SceneManager::GetInstance()->LoadScene(new SceneStageSelect());
	}
	m_rootNode->TreeUpdate();
}

void SceneTitle::Draw()
{
	m_rootNode->TreeDraw();
}

void SceneTitle::LateDraw()
{
	m_rootNode->TreeLateDraw();
}
