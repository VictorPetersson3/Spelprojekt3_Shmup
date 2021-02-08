#pragma once
#include "GameObject.h"
#include "Enums.h"
namespace Studio
{
	class PowerUpModule : public GameObject
	{
	public:
		PowerUpModule(Enums::PowerUpModules aPowerUpModule);
		void Update();
		bool GetIsShield();
	private:
		bool myIsShield = false;
	};
}


