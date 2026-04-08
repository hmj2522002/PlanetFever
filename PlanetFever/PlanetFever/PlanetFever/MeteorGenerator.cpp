#include "MeteorGenerator.h"
#include "Meteor.h"

MeteorGenerator::MeteorGenerator() :
	m_spanFrame(180),
	m_deltaFrame(0)
{

}

void MeteorGenerator::Load()
{
	Node::Load();
}

void MeteorGenerator::Release()
{
	Node::Release();
}

void MeteorGenerator::Update()
{
	m_deltaFrame++;

	if (m_spanFrame <= m_deltaFrame)
	{
		m_spawnDir = Vector2::AngleToDirect(rand() % 360);

		m_deltaFrame = 0;
		GetParent()->AddChild(new Meteor(Ore::OreType::Coal ,m_spawnDir));
	}



	Node::Update();
}

void MeteorGenerator::Draw()
{
	Node::Draw();
}
