#include "stdafx.h"
#include "Boss.h"
namespace Studio
{
	Boss::Boss()
	{
	}

	Boss::Boss(Tga2D::CSprite* aSprite, VECTOR2F aSpawnPosition) : 
		Boss::GameObject(aSprite)
	{
		myPosition = aSpawnPosition;
		myPhaseCount = 0;
	}

	Boss::~Boss()
	{
	}

}
