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
	seCount01(0),
	seCount02(0),
	inGame(false)
{
	seStart = LoadSoundMem("Sounds/se_start.mp3");
	seFinish = LoadSoundMem("Sounds/se_finish.mp3");
	seCount01 = LoadSoundMem("Sounds/se_count01.mp3");
	seCount02 = LoadSoundMem("Sounds/se_count02.mp3");
	ChangeVolumeSoundMem(200, seCount02);
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

	if (timeFrameLeft < StartTimeLeftSound)
	{
		if (prevTimeFrameLeft % 100 < timeFrameLeft % 100)
		{
			PlaySoundMem(seCount01, DX_PLAYTYPE_BACK);
		}
		else if (prevTimeFrameLeft % 10 < timeFrameLeft % 10)
		{
			PlaySoundMem(seCount02, DX_PLAYTYPE_BACK);
		}
	}

	if (timeFrameLeft == TimeFrameLeft)
	{
		PlaySoundMem(seStart, DX_PLAYTYPE_BACK);
	}
	prevTimeFrameLeft = timeFrameLeft;
	timeFrameLeft--;
}
