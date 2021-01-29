#include "stdafx.h"
#include "MenuManagerSingleton.h"


namespace Studio
{
	namespace MenuManagerSingleton
	{
		namespace
		{
			MenuManager* myMenuManager;
		}

		void Construct(Studio::Player* aPlayer)
		{
			myMenuManager = new MenuManager(aPlayer);
		}

		MenuManager* GetInstance()
		{
			return myMenuManager;
		}

		void Destruct()
		{
			delete myMenuManager;
			myMenuManager = nullptr;
		}
	}
}
