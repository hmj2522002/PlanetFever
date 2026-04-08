#include "SceneLoading.h"
#include "DxLib.h"

void SceneLoading::Initialize()
{
	m_rootNode = new Node();
}

void SceneLoading::Finalize()
{
	if (m_rootNode)
	{
		m_rootNode->TreeRelease();
		delete m_rootNode;
		m_rootNode = nullptr;
	}
}

void SceneLoading::Update()
{
	m_rootNode->TreeUpdate();
}

void SceneLoading::Draw()
{
	// ˆÃ“]
	DrawBoxAA(0, 0, Screen::Width, Screen::Height, GetColor(0, 0, 0), true);

	m_rootNode->TreeDraw();
}
