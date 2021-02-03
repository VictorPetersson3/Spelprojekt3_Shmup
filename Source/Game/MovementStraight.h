#pragma once
#include "Movement.h"
namespace Studio
{
	class MovementStraight : public Movement
	{
	public:
		MovementStraight(VECTOR2F* anObjectsPosition, float aSpeed);

		void SetMovementStartPosition(VECTOR2F* aPosition) override;

		void Update() override;
	};
}
