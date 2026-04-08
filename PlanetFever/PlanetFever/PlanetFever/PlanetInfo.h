#pragma once
#include "Ore.h"
#include <vector>
#include <list>

class SaveData;

class PlanetInfo
{
private:
	struct SpawnOreType
	{
		std::list<Ore::OreType> oreType;
	};

public:
	int nowStage;

	// 惑星名
	enum class PlanetName
	{
		CoalFallingPlanet,		// コールフォール星
		MetalAndSilverPlanet,	// メタシルバ星
		CopperGlowPlanet,		// ドードーグロウ星
		GoldFeverPlanet,		// ゴールドフィバー星
		BluelyShinyPlanet,		// ブルーリーシャイニー星
	
		Length,					// ステージ数
	};

	static constexpr int MaxStage = static_cast<int>(PlanetName::Length);

	// 惑星ごとの開放コスト
	static constexpr int PlanetCosts[MaxStage] =
	{
		0,
		3000,
		8000,
		15000,
		24000
	};

	// 惑星ごとの半径
	static constexpr float PlanetRadius[MaxStage]
	{
		92.0f,
		92.0f,
		92.0f,
		92.0f,
		92.0f
	};

	// 惑星ごとの出現する鉱石
	SpawnOreType spawnOres[MaxStage]{};

	PlanetInfo() :
		nowStage(0)
	{
		AddSpawnOre(PlanetName::CoalFallingPlanet, Ore::OreType::Coal);

		AddSpawnOre(PlanetName::MetalAndSilverPlanet, Ore::OreType::Silver);
		AddSpawnOre(PlanetName::MetalAndSilverPlanet, Ore::OreType::Iron);
	}

	// シングルトン取得
	static PlanetInfo* GetInstance()
	{
		static PlanetInfo instance;
		return &instance;
	}

	float GetNowPlanetRadius();
private:
	// 惑星ごとに出現する鉱石を追加する
	void AddSpawnOre(PlanetName name, Ore::OreType type)
	{
		spawnOres[static_cast<int>(name)].oreType.push_back(type);
	}

};
