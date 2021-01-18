#pragma once
#include<vector>
#include "MenuObject.h"

namespace Studio
{
	class MenuManager
	{
	public:
		MenuManager();
		~MenuManager();

		MenuObject* GetMainMenu();
		MenuObject* GetHUD();
		MenuObject* GetPauseMenu();

		void Render();

	private:
		MenuObject myMainMenu;
		MenuObject myHud;
		MenuObject myPausMenu;

		UIElement* testButton;
	};
}

