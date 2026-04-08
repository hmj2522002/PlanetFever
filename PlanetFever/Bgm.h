#pragma once

class Bgm
{
private:
	static constexpr int TransitionTimeFrame = 60;

	float soundVol;
	int nowBgmType;
	int nextBgmType;
	int prevBgmType;
	int transition;
	bool isPlay;
	bool isTransition;
	bool dummy = false;

public:
	Bgm();

	// 流すBGMの種類
	enum class BgmType
	{
		Rest,	// タイトルやステージ選択画面
		Main,	// ゲーム画面

		Length
	};

	// それぞれのBGM名
	const char* BgmNames[static_cast<int>(BgmType::Length)] =
	{
		"Sounds/bgm_rest.mp3",
		"Sounds/bgm_game.mp3"
	};

	static Bgm* GetInstance()
	{
		static Bgm instance;
		return &instance;
	}

	void Update();
	void Draw();

	void ChangeBgm(BgmType type)
	{
		int num = static_cast<int>(type);

		if (nowBgmType == num) return;
		if (static_cast<int>(BgmType::Length) <= num)
		{
			num = static_cast<int>(BgmType::Length) - 1;
		}

		nextBgmType = num;	
	}

	void Stop()
	{
		isTransition = true;
	}

private:
	int bgmHandles[static_cast<int>(BgmType::Length)];
};
