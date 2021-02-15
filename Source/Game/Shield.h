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
		void Update(VECTOR2F aPosition);
		void HitLogic(float aDamage);
		HealthBar* GetHealthBar();

	private:
		HealthBar myHealthBar;
		VECTOR2F myCenter;
	};

}

