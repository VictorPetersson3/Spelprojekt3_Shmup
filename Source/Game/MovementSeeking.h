#pragma once
#include "Movement.h"
namespace Studio
{
	class MovementSeeking : public Movement
	{
	public:
		MovementSeeking(VECTOR2F* anObjectsPosition, VECTOR2F aTargetObjectsPosition, float aNormalSpeed, float anAcceleratedSpeed);

		void SetMovementStartPosition(VECTOR2F* aPosition) override;

		void Update() override;
	private:
		bool myIsLevelWithTarget;
		float myAcceleratedSpeed;

		VECTOR2F myTargetObjectsPosition;
	};
}
