#include "GameInfo.h"

void GameInfo::Update()
{

	if (IsTimeUp()) 
	{
		timeFrameLeft = 0;
		return;
	}
	timeFrameLeft--;
}
