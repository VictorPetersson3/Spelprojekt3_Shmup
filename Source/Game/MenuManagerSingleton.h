#pragma once
#include "MenuManager.h"
#include "Player.h"

namespace Studio
{
	namespace MenuManagerSingleton
	{
		MenuManager* GetInstance();

		void Construct(Studio::Player* aPlayer);
		void Destruct();
	}
}

