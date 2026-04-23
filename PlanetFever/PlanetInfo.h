#pragma once
#include <list>
#include <vector>

class PlanetInfo
{
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
		800,
		2000,
		4500,
		8000
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

	// 惑星ごとの隕石出現間隔倍率
	static constexpr float SpawnMeteorMagnifications[MaxStage]
	{
		0.8f,
		1.0f,
		1.5f,
		1.2f,
		0.8f
	};

	// 鉱石名
	enum class OreType
	{
		Coal,		// 石炭
		Silver,		// 銀
		Iron,		// 鉄
		Copper,		// 銅
		Gold,		// 金
		Sapphire,	// サファイア

		Length
	};

	// 鉱石の価値（スコア）
	static constexpr int OrePrice[static_cast<int>(OreType::Length)]
	{
		 60,
		 70,
		 75,
		 45,
		100,
		120,
	};

	// 隕石ごとの体力
	static constexpr int MeteorHP[static_cast<int>(OreType::Length)]
	{
		100,
		120,
		150,
		 60,
		120,
		220,
	};

	struct SpawnOreType
	{
		std::vector<OreType> oreType;	// 鉱石の種類
		std::list<int> oreWeight;		// 鉱石のドロップ割合
	};

	// 惑星ごとの出現する鉱石
	SpawnOreType spawnOres[MaxStage]{};

	PlanetInfo() :
		nowStage(0)
	{
		// それぞれの惑星に降ってくる隕石と、その確率を設定
		AddSpawnOre(PlanetName::CoalFallingPlanet,		OreType::Coal,	   100);

		AddSpawnOre(PlanetName::MetalAndSilverPlanet,	OreType::Silver,	50);
		AddSpawnOre(PlanetName::MetalAndSilverPlanet,	OreType::Iron,		50);

		AddSpawnOre(PlanetName::CopperGlowPlanet,		OreType::Copper,	80);
		AddSpawnOre(PlanetName::CopperGlowPlanet,		OreType::Coal,		20);

		AddSpawnOre(PlanetName::GoldFeverPlanet,		OreType::Gold,		70);
		AddSpawnOre(PlanetName::GoldFeverPlanet,		OreType::Silver,	15);
		AddSpawnOre(PlanetName::GoldFeverPlanet,		OreType::Coal,		15);

		AddSpawnOre(PlanetName::BluelyShinyPlanet,		OreType::Sapphire, 100);
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
	void AddSpawnOre(PlanetName name, OreType type, int weight)
	{
		spawnOres[static_cast<int>(name)].oreType.push_back(type);
		spawnOres[static_cast<int>(name)].oreWeight.push_back(weight);
	}

};
