#pragma once
#include "Movement.h"

namespace Studio
{
	class MovementWave : public Movement
	{
	public:
		MovementWave(VECTOR2F* anObjectsPosition, float aHorizontalSpeed, float aVerticalSpeed, float aWaveHeight);

		void SetMovementStartPosition(VECTOR2F* aPosition) override;

		void Update() override;
	private:
		float myWaveHeight;
		float mySpawnYPos;
		float myHorizontalSpeed;
		float myVerticalSpeed;

		const float myCalculatedSpeed;
	};
}


