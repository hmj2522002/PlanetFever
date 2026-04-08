#include "SceneResult.h"
#include "Animation2D.h"
#include "SceneStageSelect.h"
#include "Input.h"
#include "GameInfo.h"
#include "SaveData.h"
#include "LargeText.h"

SceneResult::SceneResult()
{
	m_rootNode = new Node();

	m_rootNode->AddChild(new Actor2D("Resource/BG.png"));

	m_rootNode->AddChild(new LargeText(LargeText::Text::ClickToBack, Screen::Center + TextOffset, true));

	SaveData* saveData = SaveData::GetInstance();
	int totalScore = 0;

	saveData->SetScore(saveData->GetScore() + 200);
}

void SceneResult::Initialize()
{

}

void SceneResult::Finalize()
{
	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		m_rootNode = nullptr;
		delete m_rootNode;
	}
}

void SceneResult::Update()
{
	if (m_rootNode)
	{
		m_rootNode->TreeUpdate();
	}

	if (Mouse::IsAnyPress())
	{
		SceneManager::GetInstance()->LoadScene(new SceneStageSelect());
	}
}

void SceneResult::Draw()
{
	if (m_rootNode)
	{
		m_rootNode->TreeDraw();
	}
}

void SceneResult::LateDraw()
{
	if (m_rootNode)
	{
		m_rootNode->TreeLateDraw();
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 120);
	DrawBox(0, 0, Screen::Width, Screen::Height, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
