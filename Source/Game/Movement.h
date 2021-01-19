#pragma once
#include "Enums.h"
namespace Studio
{
	class Movement
	{
	public:
		Movement(VECTOR2F *aPos, Enums::MovementPattern aMovementType);
		~Movement();
		void Straight(VECTOR2F* aPos, float aSpeed);
		void Wave(VECTOR2F* aPos, float aWaveSpeed, float aSpeed, float aHeight);
		void Diagonal(VECTOR2F* aPos, float aSpeed, float aY, float anAngle);
		void Homing(VECTOR2F* aPos, float aSpeed);

		void Update(float aSpeed);
	private:
		VECTOR2F* myPos;
		Enums::MovementPattern myMovementType;
	};
}


