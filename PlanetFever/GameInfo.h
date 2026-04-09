#pragma once
#include "Ore.h"
#include "SaveData.h"
#include <list>
#include <vector>
#include <iterator>
#include <unordered_map>

// １ゲーム内の情報
class GameInfo
{
public:
	static constexpr int TimeFrameLeft = 5000;

private:
	static constexpr int WaitStartTimeFrame = 120;
	static constexpr int StartTimeLeftSound = 1000;

	int score;
	int prevTotalScore;
	int timeFrameLeft;		// 残り時間（フレーム）
	int prevTimeFrameLeft;	// １フレ前残り時間
	int waitStart;
	int seStart;
	int seFinish;
	int seCount01;
	int seCount02;
	bool inGame;

public:
	GameInfo();

	void Update();

	// 入手鉱石
	std::vector<PlanetInfo::OreType> getOreTypes;
	std::unordered_map<PlanetInfo::OreType, int> getOreAmount;	// 入手した鉱石の種類の数

	static GameInfo* GetInstance()
	{
		static GameInfo instance;
		return &instance;
	}

	// SceneStageSelectに戻ったら実行するように
	void Reset()
	{
		score = 0;
		prevTotalScore = SaveData::GetInstance()->GetScore();
		timeFrameLeft = TimeFrameLeft;
		waitStart = WaitStartTimeFrame;
		inGame = false;

		getOreTypes.clear();
		getOreAmount.clear();
	}

	int GetTimeLeft() const
	{
		return timeFrameLeft;
	}

	// 入手した鉱石をリストに追加
	void AddCollectOre(PlanetInfo::OreType type, int amount = 1)
	{
		// リストにtypeが無かったら勝手に追加してくれるらしい...
		// そしてtype番目の数値を書き換える
		getOreAmount[type] += amount;

		bool containType = false;
		for (auto check : getOreTypes)
		{
			if (type == check)
			{
				containType = true;
				break;
			}
		}

		if (!containType) getOreTypes.push_back(type);
	}

	bool IsTimeUp() const
	{
		return timeFrameLeft <= 0;
	}

	bool InGame() const
	{
		return !IsTimeUp() && waitStart <= 0;
	}

	// 指定した鉱石を何個手に入れたかを取得
	int GetOreAmountAtList(PlanetInfo::OreType type) const
	{
		return getOreAmount.at(type);
	}

	// 前回ステージ攻略前の総合スコアを取得
	int GetPrevTotalScore() const
	{
		return prevTotalScore;
	}

	// スコアを設定（指定）
	void SetScore(int _score)
	{
		score = _score;
	}

	// スコアを設定（増減）
	void AddScore(int _score)
	{
		score += _score;
	}

	// スコアを取得
	int GetScore() const
	{
		return score;
	}
};
