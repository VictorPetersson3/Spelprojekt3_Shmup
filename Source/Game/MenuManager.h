#pragma once
#include<vector>
#include "MenuObject.h"
#include "TestButton.h"
#include "UIElement.h"

namespace Studio
{
	class MenuManager
	{
	public:
		MenuManager();

		MenuObject* GetMainMenu();
		MenuObject* GetHUD();
		MenuObject* GetPauseMenu();

		void Render();
		void Update();

	private:
		MenuObject myMainMenu;
		MenuObject myHud;
		MenuObject myPausMenu;

		//UIElement myTestButton = TestButton("Sprites/debugpixel.dds", { 0.1f,0.8f }, { 2,2 }, { 0.5f,0.5f });;
	};


}

