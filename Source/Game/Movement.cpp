#include "stdafx.h"
#include "Movement.h"
#include "Timer.h"

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

void Movement::Wave(VECTOR2F& aPos, float aSpeed, float aMaxYValue, float aMinYValue)
{

}

void Movement::Diagonal(VECTOR2F& aPos, float aSpeed)
{
}

void Movement::Homing(VECTOR2F& aPos, float aSpeed)
{
}
