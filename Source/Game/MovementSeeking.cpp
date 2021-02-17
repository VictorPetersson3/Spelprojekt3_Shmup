#include "stdafx.h"
#include "MovementSeeking.h"
#include "Timer.h"
namespace Studio
{
	MovementSeeking::MovementSeeking(VECTOR2F* anObjectsPosition, VECTOR2F aTargetObjectsPosition, float aNormalSpeed, float anAcceleratedSpeed)
	{
		this->myObjectsPosition = anObjectsPosition;
		myPattern = Enums::MovementPattern::Seeking;
		mySpeed = aNormalSpeed;
		myAcceleratedSpeed = anAcceleratedSpeed;
		myIsLevelWithTarget = false;
		myTargetObjectsPosition = aTargetObjectsPosition;
	}

	void MovementSeeking::SetMovementStartPosition(VECTOR2F* aPosition)
	{
		this->myObjectsPosition = aPosition;
	}

	void MovementSeeking::Update()
	{
		myDirection = *myObjectsPosition;
		myObjectsPosition->x -= mySpeed * Timer::GetInstance()->TGetDeltaTime();
		if (!myIsLevelWithTarget)
		{
			if (myObjectsPosition->y < myTargetObjectsPosition.y + 2 && myObjectsPosition->y > myTargetObjectsPosition.y - 2)
			{
				myIsLevelWithTarget = true;
				mySpeed = myAcceleratedSpeed;

			}
			else if (myObjectsPosition->y < myTargetObjectsPosition.y)
			{
				myObjectsPosition->y += mySpeed * 0.5 * Timer::GetInstance()->TGetDeltaTime();
				printf_s("%f\n%f", myObjectsPosition->y, myTargetObjectsPosition.y);

			}
			else if (myObjectsPosition->y > myTargetObjectsPosition.y)
			{
				myObjectsPosition->y -= mySpeed * 0.5 * Timer::GetInstance()->TGetDeltaTime();
				printf_s("%f\n%f\n", myObjectsPosition->y, myTargetObjectsPosition.y);
			}
		}
		myDirection = (myDirection - *myObjectsPosition).GetNormalized();
	}
}