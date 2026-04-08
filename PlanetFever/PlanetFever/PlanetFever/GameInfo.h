#pragma once
#include "Ore.h"
#include "SaveData.h"
#include <list>
#include <iterator>
#include <unordered_map>

class GameInfo
{
private:
	static constexpr int TimeFrameLeft = 3000;

	//std::list<Ore::OreType> getOreType;	// 入手した鉱石の種類
	//std::list<int> getOreAmount;		// 入手した鉱石の数

	std::unordered_map<Ore::OreType, int> getOres;	// 入手した鉱石の種類、数

	int score;
	int prevTotalScore;
	int timeFrameLeft;
	bool inGame;

public:
	GameInfo() :
		score(0),
		prevTotalScore(0),
		timeFrameLeft(TimeFrameLeft),
		inGame(false)
	{}

	void Update();

	static GameInfo* GetInstance()
	{
		static GameInfo instance;
		return &instance;
	}

	void Reset()
	{
		score = 0;
		prevTotalScore = SaveData::GetInstance()->GetScore();
		timeFrameLeft = TimeFrameLeft;
		inGame = false;
	}

	int GetTimeLeft() const
	{
		return timeFrameLeft;
	}

	// 入手した鉱石をリストに追加
	void AddCollectOre(Ore::OreType type, int amount = 1)
	{
		// リストにtypeが無かったら勝手に追加してくれるらしい...
		// そしてtype番目の数値を書き換える
		getOres[type] += amount;
	}

	bool IsTimeUp() const
	{
		return timeFrameLeft <= 0;
	}

	// 指定した鉱石を何個手に入れたかを取得
	int GetOreAmountAtList(Ore::OreType type) const
	{
		return getOres.at(type);
	}

	// 前回ステージ攻略前の総合スコアを取得
	int GetPrevTotalScore() const
	{
		return prevTotalScore;
	}
};
