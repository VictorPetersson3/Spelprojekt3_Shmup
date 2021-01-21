#pragma once
#include "Movement.h"
namespace Studio
{
	class MovementDiagonal : public Movement
	{
	public:
		MovementDiagonal(VECTOR2F* anObjectsPosition, float aSpeed, float anAngle);
		void Update() override;
	private:
		float myAngle;
	};
}
