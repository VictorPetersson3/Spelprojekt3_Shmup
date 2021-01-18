#include "stdafx.h"
#include "Movement.h"
#include "Timer.h"
#include <math.h>

namespace Studio
{
	Movement::Movement()
	{
	}

	Movement::~Movement()
	{
	}

	void Movement::Straight(VECTOR2F& aPos, float aSpeed)
	{
		aPos.x -= aSpeed * Studio::Timer::GetInstance()->TGetDeltaTime();
	}

	void Movement::Wave(VECTOR2F& aPos, float aWaveSpeed, float aSpeed, float aHeight)
	{
		aPos.x -= aSpeed * Studio::Timer::GetInstance()->TGetDeltaTime();
		aPos.y = sin(aPos.x * aWaveSpeed) * (aHeight * 0.5f) + 0.5f;
		
	}

	void Movement::Diagonal(VECTOR2F& aPos, float aSpeed, float aY, float anAngle)
	{
		aPos.x -= aSpeed * Studio::Timer::GetInstance()->TGetDeltaTime();
		aPos.y = (aPos.x * anAngle) + 0.5f;
	}

	void Movement::Homing(VECTOR2F& aPos, float aSpeed)
	{

	}
}

