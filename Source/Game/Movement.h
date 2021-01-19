#pragma once

namespace Studio
{
	namespace Enums
	{
		enum class MovementType
		{
			None,
			Straight,
			Wave,
			Diagonal,
			Bobbing,
			UTurn,
			Homing,
			Seeking,
			Count
		};
	}

	class Movement
	{
	public:
		Movement(VECTOR2F *aPos);
		~Movement();
		void Straight(VECTOR2F& aPos, float aSpeed);
		void Wave(VECTOR2F& aPos, float aWaveSpeed, float aSpeed, float aHeight);
		void Diagonal(VECTOR2F& aPos, float aSpeed, float aY, float anAngle);
		void Homing(VECTOR2F& aPos, float aSpeed);

		void Update();
	private:
		VECTOR2F* myPos;
	};
}


