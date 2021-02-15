#pragma once
#include "GameObject.h"
namespace Studio
{
	class Laser : public GameObject
	{
	public:
		Laser(VECTOR2F aPosition);
		~Laser();

		void Update(float anY);

		float GetDamage();
	private:
		float myDamage;
		

		VECTOR2F myPosition;
	};
}

