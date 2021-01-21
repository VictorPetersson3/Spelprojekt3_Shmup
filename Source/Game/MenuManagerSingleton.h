#pragma once
#include "MenuManager.h"


namespace Studio
{
	namespace MenuManagerSingleton
	{
		MenuManager* GetInstance();

		void Construct();
		void Destruct();
	}
}

