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

		TestButton myTestButton = TestButton("Sprites/debugpixel.dds", { 250,900 }, { 200,200 }, { 0.5f,0.5f });
	};


}

