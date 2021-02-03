#pragma once
#include "Movement.h"
namespace Studio
{
	class MovementDiagonal : public Movement
	{
	public:
		MovementDiagonal(VECTOR2F* anObjectsPosition, float aSpeed, VECTOR2F anAngle);

		void SetMovementStartPosition(VECTOR2F* aPosition) override;

		void Update() override;
	private:
		VECTOR2F myAngle;
	};
}
