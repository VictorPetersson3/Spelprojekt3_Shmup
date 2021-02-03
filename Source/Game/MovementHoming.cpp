#include "stdafx.h"
#include "MovementHoming.h"
#include "Timer.h"
#include "Player.h"
namespace Studio
{
	MovementHoming::MovementHoming(GameObject* anObject, VECTOR2F* anObjectsPosition, float aSpeed, float aRotationSpeed, float aDirection)
	{
		// TODO: Change into initializer

		myObject = anObject;
		myObjectsPosition = anObjectsPosition;

		mySpeed = aSpeed;
		myRotationSpeed = aRotationSpeed;
		myDirection = aDirection;
	}

	void MovementHoming::SetMovementStartPosition(VECTOR2F* aPosition)
	{
		this->myObjectsPosition = aPosition;
	}

	void MovementHoming::Update()
	{
		float deltaTime = Timer::GetInstance()->TGetDeltaTime();

		/*float rotation = myObject->GetRotation();

		myObjectsPosition->x -= std::sin(rotation) * mySpeed * deltaTime;
		myObjectsPosition->y -= std::cos(rotation) * mySpeed * deltaTime;

		auto v1 = myObjectsPosition;
		VECTOR2F v2 = { 0.5f * SCREEN_WIDTH, 0.5f * SCREEN_HEIGHT };

		float v1_theta = std::atan2(v1->y, v1->x);
		float v2_theta = std::atan2(v2.y, v2.x);

		float r = (v2_theta - v1_theta) * (180.0 / std::acos(-1.0f));

		if (r < 0)
			r = std::fmod(r, 360);

		myDirection = r;
		myObject->SetRotation(myDirection);*/

		VECTOR2F target = { 0.25f * SCREEN_HEIGHT, 0.25f * SCREEN_HEIGHT };

		if (myObjectsPosition->x < target.x)
		{
			myVelocity.x += mySpeed * deltaTime;
		}
		if (myObjectsPosition->x > target.x)
		{
			myVelocity.x -= mySpeed * deltaTime;
		}
		if (myObjectsPosition->y < target.y)
		{
			myVelocity.y += mySpeed * deltaTime;
		}
		if (myObjectsPosition->y > target.y)
		{
			myVelocity.y -= mySpeed * deltaTime;
		}

#define magic_number 100.0f

		if (myVelocity.x > magic_number)
		{
			myVelocity.x = magic_number;
		}
		if (myVelocity.x < -magic_number)
		{
			myVelocity.x = -magic_number;
		}
		if (myVelocity.y > magic_number)
		{
			myVelocity.y = magic_number;
		}
		if (myVelocity.y < -magic_number)
		{
			myVelocity.y = -magic_number;
		}

		*myObjectsPosition += myVelocity * deltaTime;
	}
}