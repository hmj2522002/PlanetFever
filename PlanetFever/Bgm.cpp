#include "Bgm.h"
#include "DxLib.h"

Bgm::Bgm() :
	soundVol(0),
	nowBgmType(-1),
	nextBgmType(-1),
	prevBgmType(-1),
	transition(TransitionTimeFrame),
	isPlay(false),
	isTransition(false)
{
	for (int i = 0; i < static_cast<int>(BgmType::Length); i++)
	{
		int handle = LoadSoundMem(BgmNames[i]);
		bgmHandles[i] = handle;
	}
}

void Bgm::Update()
{
	// 次再生するBGMがあるなら切り替え
	if (0 <= nextBgmType)
	{
		if (!isTransition)
		{
			// 現在再生されているBGMがないならサッサと切り替える
			transition = nowBgmType != -1 ?
				TransitionTimeFrame : 0;
			isTransition = true;
		}
		else
		{
			if (0 < transition)
			{
				transition--;
			}
		}
	}

	if (isTransition && transition <= 0)
	{
		// 現在のBGMを止める
		if (0 <= nowBgmType)
		{
			StopSoundMem(bgmHandles[nowBgmType]);
		}

		nowBgmType = -1;
		isTransition = false;
		transition = TransitionTimeFrame;
	}

	// 現在再生されているBGMが無かったら次再生するBGMを準備
	if (nowBgmType == -1)
	{
		if (0 <= nextBgmType)
		{
			nowBgmType = nextBgmType;
			nextBgmType = -1;
		}
	}

	// 前フレームで再生しているBGMが違っていたら新しいBGMを再生する
	if (nowBgmType != prevBgmType)
	{
		if (0 <= nowBgmType && nowBgmType < static_cast<int>(BgmType::Length))
		{
			dummy = true;
			PlaySoundMem(bgmHandles[nowBgmType], DX_PLAYTYPE_LOOP);
			isPlay = true;
			isTransition = false;
		}
	}

	if (0 <= nowBgmType && nowBgmType < static_cast<int>(BgmType::Length))
	{
		ChangeVolumeSoundMem(static_cast<int>(
			(static_cast<float>(transition) / static_cast<float>(TransitionTimeFrame))
			* 255),
			bgmHandles[nowBgmType]);
	}

	prevBgmType = nowBgmType;
}

void Bgm::Draw()
{

}

