#include "stdafx.h"
#include "MovementDiagonal.h"
#include "Timer.h"

namespace Studio
{
	MovementDiagonal::MovementDiagonal(VECTOR2F* anObjectsPosition, float aSpeed, VECTOR2F anAngle)
	{
		this->myObjectsPosition = anObjectsPosition;
		myPattern = Enums::MovementPattern::Diagonal;
		mySpeed = aSpeed;
		myAngle = anAngle;
		myTotalTime = 0.0f;
	}
	void MovementDiagonal::SetMovementStartPosition(VECTOR2F* aPosition)
	{
		this->myObjectsPosition = aPosition;
	}
	void MovementDiagonal::Update()
	{
		myDirection = myAngle;
		myTotalTime += Timer::GetInstance()->TGetDeltaTime();
		myObjectsPosition->x += myAngle.x * mySpeed * Timer::GetInstance()->TGetDeltaTime();
		myObjectsPosition->y += myAngle.y * mySpeed * Timer::GetInstance()->TGetDeltaTime();
	}
}