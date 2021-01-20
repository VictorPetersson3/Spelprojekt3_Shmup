#include "stdafx.h"
#include "MovementStraight.h"
#include "Timer.h"

namespace Studio
{
	MovementStraight::MovementStraight(VECTOR2F* anObjectsPosition, float aSpeed)
	{
		this->myObjectsPosition = anObjectsPosition;
		myPattern = Enums::MovementPattern::Straight;
		mySpeed = aSpeed;
	}

	void MovementStraight::Update()
	{
		float deltaTime = Timer::GetInstance()->TGetDeltaTime();

		myObjectsPosition->x -= mySpeed * deltaTime;

	}
}

