#include "stdafx.h"
#include "MovementBobbing.h"
#include "Timer.h"
namespace Studio
{
	MovementBobbing::MovementBobbing(VECTOR2F* anObjectsPosition, float aVerticalSpeed, float aWaveHeight) :
		//Conversion from pixel-per-second to normalised
		myCalculatedSpeed(std::acos(-1) / (aWaveHeight / aVerticalSpeed))
	{
		this->myObjectsPosition = anObjectsPosition;
		myPattern = Enums::MovementPattern::Wave;
		myVerticalSpeed = aVerticalSpeed;
		myWaveHeight = aWaveHeight;
		myTotalTime = 0.0f;
		mySpawnYPos = anObjectsPosition->y;

	}

	void MovementBobbing::Update()
	{
		myTotalTime += Timer::GetInstance()->TGetDeltaTime();
		myObjectsPosition->y = -sinf(myTotalTime * myCalculatedSpeed) * myWaveHeight * 0.5f + mySpawnYPos;
		printf("\n%f", std::acos(-1) / (myWaveHeight / myVerticalSpeed));
	}
}

