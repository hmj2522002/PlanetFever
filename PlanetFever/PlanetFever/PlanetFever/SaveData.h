#pragma once
#include "PlanetInfo.h"


// ゲームの主なデータ管理。シーンゲーム、リザルト遷移時点で上書きする
class SaveData
{
private:
	int totalExp;						// 総合経験値
	int totalScore;						// 総合スコア
	PlanetInfo::PlanetName prevStage;	// 前回プレイしたステージ
	PlanetInfo::PlanetName openedStage;	// これまでに解放したステージ

public:
	SaveData() :
		totalExp(0),
		totalScore(0),
		prevStage(PlanetInfo::PlanetName::CoalFallingPlanet),
		openedStage(PlanetInfo::PlanetName::CoalFallingPlanet)
	{}

	static SaveData* GetInstance()
	{
		static SaveData instance;
		return &instance;
	}

	void SetExp(int exp) { totalExp = exp; }
	int GetExp() const { return totalExp; }

	void SetScore(int score) { totalScore = score; }
	int GetScore() const { return totalScore; }

	void SetStage(PlanetInfo::PlanetName stage) { prevStage = stage; }
	PlanetInfo::PlanetName GetStage() const { return prevStage; }

	void SetOpenedStage(PlanetInfo::PlanetName stage) { openedStage = stage; }
	PlanetInfo::PlanetName GetOpenedStage() const { return openedStage; }
};
