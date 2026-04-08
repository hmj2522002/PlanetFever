#include "PlanetInfo.h"
#include "SaveData.h"

float PlanetInfo::GetNowPlanetRadius()
{
	return PlanetInfo::PlanetRadius[static_cast<int>(SaveData::GetInstance()->GetStage())];
}

