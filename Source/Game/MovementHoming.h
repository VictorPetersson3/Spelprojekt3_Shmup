#pragma once
#include "Movement.h"

namespace Studio
{
	class Player;
	class GameObject;
	class MovementHoming : public Movement
	{
	public:
		MovementHoming(GameObject* anObject, VECTOR2F* anObjectsPosition, float aSpeed, float aRotationSpeed, float aDirection = 0.0f);

		void SetMovementStartPosition(VECTOR2F* aPosition) override;

		void Update() override;
	private:
		float myRotationSpeed;
		float myDirection;
		GameObject* myObject;
		VECTOR2F* myTargetPosition;
		VECTOR2F myVelocity;
	};
}
