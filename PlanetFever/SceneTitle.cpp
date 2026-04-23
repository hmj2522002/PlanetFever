#include "SceneTitle.h"
#include "Animation2D.h"
#include "SceneStageSelect.h"
#include "Input.h"
#include "Bgm.h"
#include "Fade.h"
#include "SaveData.h"

SceneTitle::SceneTitle() :
	m_seNext(0)
{
	m_rootNode = new Node();

	m_rootNode->AddChild(new Actor2D("Resource/BG.png"));

	m_rootNode->AddChild(new Actor2D(
		"Resource/logo.png",
		Tag::None,
		Layer::Object,
		Transform2D(Screen::Center + LogoOffset
		)
	));

	m_largeText = new LargeText(
		LargeText::Text::ClickToStart,
		Vector2(Screen::Width / 2.0f, Screen::Height) + TextOffset,
		true
	);
	m_rootNode->AddChild(m_largeText);
}

void SceneTitle::Initialize()
{
	Bgm::GetInstance()->ChangeBgm(Bgm::BgmType::Rest);

	m_seNext = LoadSoundMem("Sounds/se_next.mp3");
}

void SceneTitle::Finalize()
{
	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}

	DeleteSoundMem(m_seNext);
}

void SceneTitle::Update()
{
	if (Mouse::IsDown(MOUSE_INPUT_LEFT) && !Fade::GetInstance()->IsFade())
	{
		SceneManager::GetInstance()->LoadScene(new SceneStageSelect());
		PlaySoundMem(m_seNext, DX_PLAYTYPE_BACK);
	}
	m_rootNode->TreeUpdate();

#ifdef _DEBUG
	if (Keyboard::IsDown(KEY_INPUT_SPACE))
	{
		SaveData::GetInstance()->SetScore(4000);
	}
#endif
}

void SceneTitle::Draw()
{
	m_rootNode->TreeDraw();
}

void SceneTitle::LateDraw()
{
	m_rootNode->TreeLateDraw();

	m_largeText->UIDraw();
}
