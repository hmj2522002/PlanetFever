#include "MeteorGenerator.h"
#include "Meteor.h"
#include "SaveData.h"
#include "GameInfo.h"

MeteorGenerator::MeteorGenerator() :
	m_spanFrame(DefaultSpanFrame
		/ PlanetInfo::SpawnMeteorMagnifications[static_cast<int>(
			SaveData::GetInstance()->GetStage())]),
	m_deltaFrame(0)
{
	dummy = static_cast<int>(SaveData::GetInstance()->GetStage());
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

		PlanetInfo* planetInfo = PlanetInfo::GetInstance();
		SaveData* saveData = SaveData::GetInstance();
		PlanetInfo::OreType spawnOre;
		PlanetInfo::SpawnOreType thisPlanetInfo = planetInfo->spawnOres[static_cast<int>(saveData->GetStage())];

		if (GameInfo::GetInstance()->InGame())
		{
			int spawn = 0;
			if (thisPlanetInfo.oreType.empty())
			{
				auto& type =
					planetInfo->spawnOres[0].oreType;
				spawn = rand() % type.size();
				spawnOre = type[spawn];
			}
			else
			{
				int totalWeight = 0;
				int cumulative = 0;

				for (int weight : thisPlanetInfo.oreWeight)
				{
					totalWeight += weight;
				}

				int random = rand() % totalWeight;
				int ore = 0;

				for (int weight : thisPlanetInfo.oreWeight)
				{
					cumulative += weight;

					if (random < cumulative)
					{
						spawn = ore;
						break;
					}
					ore++;
				}

				spawnOre = thisPlanetInfo.oreType[spawn];
			}

			if (GetParent())
			{
				GetParent()->AddChild(new Meteor(spawnOre, m_spawnDir));
			}
		}

		int frameLeft = GameInfo::GetInstance()->GetTimeLeft();
		int defaultFrameLeft = GameInfo::TimeFrameLeft;

		if (defaultFrameLeft * 0.75f < frameLeft)
		{
			m_spanFrame = DefaultSpanFrame * 1.2f;
		}
		else if (defaultFrameLeft * 0.50f < frameLeft)
		{
			m_spanFrame = DefaultSpanFrame * 0.9f;
		}
		else if (defaultFrameLeft * 0.30f < frameLeft)
		{
			m_spanFrame = DefaultSpanFrame * 0.7f;
		}
		else
		{
			m_spanFrame = DefaultSpanFrame * 0.5f;

			if (frameLeft < FinishSpawnFrame)
			{
				// ŽÀŽ¿“I‚É¶¬‚ð‚â‚ß‚é
				m_spanFrame = DefaultSpanFrame * 99999;
			}
		}
		// ˜f¯‚²‚Æ‚ÌoŒ»ŠÔŠu”{—¦‚ÉˆË‘¶‚³‚¹‚é
		m_spanFrame /= PlanetInfo::SpawnMeteorMagnifications[static_cast<int>(
			SaveData::GetInstance()->GetStage())];
			
	}

	Node::Update();
}

void MeteorGenerator::Draw()
{
	Node::Draw();
}
