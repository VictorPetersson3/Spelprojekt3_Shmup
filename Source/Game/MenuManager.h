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

		void Update();

		bool GameStarted();



	private:
		MenuObject myMainMenu;
		MenuObject myHud;
		MenuObject myPausMenu;

		bool hasStartedGame = false;
		
		TestButton* myTestButton = new TestButton("Sprites/UI/TempPlayButton.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f });
	};


}

