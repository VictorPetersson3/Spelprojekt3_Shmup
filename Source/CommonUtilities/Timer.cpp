#pragma once
#include "pch.h"
#include "Timer.h"
using Clock = std::chrono::high_resolution_clock;
void CommonUtilities::Timer::TUpdate()
{
	std::chrono::duration<double, std::ratio<1, 1>> deltaTime = Clock::now() - myFrameStart;
	myDeltaTime = static_cast<float>(deltaTime.count());
	myFrameStart = Clock::now();
}
float CommonUtilities::Timer::TGetDeltaTime() const
{
	return myDeltaTime * mySpeed;
}
double CommonUtilities::Timer::TGetTotalTime() const
{
	std::chrono::duration<double, std::ratio<1, 1>> totalTime = myFrameStart - myBegin;
	return totalTime.count();
}

// ========= FREEZING STUFF =========

void CommonUtilities::Timer::SetSpeed(float aSpeed)
{
	mySpeed = aSpeed;
}

const float CommonUtilities::Timer::GetSpeed() const
{
	return mySpeed;
}

void CommonUtilities::Timer::Freeze()
{
	myPreviousSpeed = mySpeed;
	mySpeed = 0.0f;
	myIsPaused = true;
}

void CommonUtilities::Timer::Resume()
{
	mySpeed = myPreviousSpeed;
	myIsPaused = false;
}

void CommonUtilities::Timer::ToggleFreeze()
{
	if (myIsPaused)
	{
		Resume();
	}
	else
	{
		Freeze();
	}
}

bool CommonUtilities::Timer::IsFrozen() const
{
	return myIsPaused;
}
