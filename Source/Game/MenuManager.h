#pragma once
#include<vector>
#include "MenuObject.h"

namespace Studio
{
	class MenuManager
	{
	public:
		MenuObject* GetMainMenu();
		MenuObject* GetHUD();
		MenuObject* GetPauseMenu();
	private:
		MenuObject myMainMenu;
		MenuObject myHud;
		MenuObject myPausMenu;
	};
}

