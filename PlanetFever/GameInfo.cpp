#include "GameInfo.h"
#include "DxLib.h"

GameInfo::GameInfo() :
	score(0),
	prevTotalScore(0),
	timeFrameLeft(TimeFrameLeft),
	prevTimeFrameLeft(0),
	waitStart(WaitStartTimeFrame),
	seStart(0),
	seFinish(0),
	inGame(false)
{
	seStart = LoadSoundMem("Sounds/se_start.mp3");
	seFinish = LoadSoundMem("Sounds/se_finish.mp3");
}

void GameInfo::Update()
{
	if (0 < waitStart)
	{
		waitStart--;
		return;
	}

	if (IsTimeUp()) 
	{
		// タイムアップになるとカウントは止まるので
		// 前フレームと数値が異なるのはタイムアップ時の１フレのみ
		if (prevTimeFrameLeft != timeFrameLeft)
		{
			PlaySoundMem(seFinish, DX_PLAYTYPE_BACK);
		}

		timeFrameLeft = 0;
		prevTimeFrameLeft = 0;
		return;
	}

	if (timeFrameLeft == TimeFrameLeft)
	{
		PlaySoundMem(seStart, DX_PLAYTYPE_BACK);
	}
	prevTimeFrameLeft = timeFrameLeft;
	timeFrameLeft--;
}
