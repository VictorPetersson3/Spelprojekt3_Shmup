#pragma once

namespace Studio
{
	class Movement
	{
	public:
		Movement();
		~Movement();
		void Straight(VECTOR2F& aPos, float aSpeed);
		void Wave(VECTOR2F& aPos, float aWaveSpeed, float aSpeed, float aHeight);
		void Diagonal(VECTOR2F& aPos, float aSpeed, float aY, float anAngle);
		void Homing(VECTOR2F& aPos, float aSpeed);
	private:

	};
}


