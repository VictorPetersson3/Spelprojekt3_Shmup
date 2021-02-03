#include "stdafx.h"
#include "MovementWave.h"
#include "Timer.h"
namespace Studio
{
	MovementWave::MovementWave(VECTOR2F* anObjectsPosition, float aHorizontalSpeed, float aVerticalSpeed, float aWaveHeight) : 
		//Conversion from pixel-per-second to normalised
		myCalculatedSpeed(std::acos(-1) / (aWaveHeight / aVerticalSpeed))
	{
		this->myObjectsPosition = anObjectsPosition;
		myPattern = Enums::MovementPattern::Wave;
		myVerticalSpeed = aVerticalSpeed;
		myHorizontalSpeed = aHorizontalSpeed;
		myWaveHeight = aWaveHeight;
		myTotalTime = 0.0f;
		mySpawnYPos = anObjectsPosition->y;

	}

	void MovementWave::SetMovementStartPosition(VECTOR2F* aPosition)
	{
		this->myObjectsPosition = aPosition;
		mySpawnYPos = aPosition->y;
	}

	void MovementWave::Update()
	{
		myTotalTime += Timer::GetInstance()->TGetDeltaTime();
		myObjectsPosition->x -= Timer::GetInstance()->TGetDeltaTime() * myHorizontalSpeed;
		myObjectsPosition->y = -sinf(myTotalTime * myCalculatedSpeed) * myWaveHeight * 0.5f + mySpawnYPos;
	}
}

