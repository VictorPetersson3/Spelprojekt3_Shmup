#pragma once
#include "GameObject.h"
#include "HealthBar.h"
namespace Studio
{
	class Shield : public GameObject
	{
	public:
		Shield(float aHitPoints);
		~Shield();
		void Update();
		void HitLogic(float aDamage);

	private:
		HealthBar myHealthBar;
		VECTOR2F myCenter;
	};

}

