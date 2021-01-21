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

		void Construct()
		{
			myMenuManager = new MenuManager();
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
