#include "SceneResult.h"
#include "Animation2D.h"
#include "SceneStageSelect.h"
#include "Input.h"
#include "GameInfo.h"
#include "SaveData.h"

SceneResult::SceneResult() :
	m_seNext(0)
{
	m_rootNode = new Node();

	m_rootNode->AddChild(new Actor2D("Resource/BG.png"));

	m_backText = new LargeText(LargeText::Text::ClickToBack, Screen::BottomCenter + BackTextOffset, true);
	m_rootNode->AddChild(m_backText);

	m_resultText = new LargeText(LargeText::Text::Result, Screen::TopCenter + ResultTextOffset);
	m_rootNode->AddChild(m_resultText);

	SaveData* saveData = SaveData::GetInstance();
	int totalScore = 0;

	saveData->SetScore(saveData->GetScore() + GameInfo::GetInstance()->GetScore());
	saveData->AddPlayCount(SaveData::GetInstance()->GetStage());

	// 前回のプレイでどれだけの種類の鉱石をゲットしたか
	int totalGetOreTypes = static_cast<int>(GameInfo::GetInstance()->getOreTypes.size());

	for (int i = 0; i < totalGetOreTypes; i++)
	{
		m_resultUIList.push_back(
			new ResultUI(
				i,
				TopResultUIpos + (ResultUIinterval * i
				)
			)
		);
	}

	if (totalGetOreTypes)
	m_resultUIList.push_back(
		new ResultUI(
			0,
			Screen::Bottom + static_cast<int>(FinalResultOffset.y),
			true
		)
	);
}

void SceneResult::Initialize()
{
	m_seNext = LoadSoundMem("Sounds/se_next.mp3");
}

void SceneResult::Finalize()
{
	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		m_rootNode = nullptr;
		delete m_rootNode;
	}

	for (auto& list : m_resultUIList)
	{
		delete list;
		list = nullptr;
	}
	m_resultUIList.clear();

	DeleteSoundMem(m_seNext);
}

void SceneResult::Update()
{
	if (m_rootNode)
	{
		m_rootNode->TreeUpdate();
	}

	if (Mouse::IsDown(MOUSE_INPUT_LEFT))
	{
		SceneManager::GetInstance()->LoadScene(new SceneStageSelect());
		PlaySoundMem(m_seNext, DX_PLAYTYPE_BACK);
	}

	for (auto list : m_resultUIList)
	{
		list->Update();
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

	m_backText->UIDraw();
	m_resultText->UIDraw();

	for (auto list : m_resultUIList)
	{
		list->Draw();
	}
}
