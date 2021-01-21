#pragma once
#include<vector>
#include "MenuObject.h"
#include "TestButton.h"
#include "UIElement.h"
#include "TextElement.h"
#include "GodModeButton.h"

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

		void Render();

		bool GameStarted();
		bool GetGodMode();

	private:
		MenuObject myMainMenu;
		MenuObject myHud;
		MenuObject myPausMenu;

		bool hasStartedGame = false;
		bool inGodMode = false;

		TestButton* myTestButton = new TestButton("Sprites/UI/TempPlayButton.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f },"StartButton");
		TextElement* myScoreText = new TextElement(Tga2D::EFontSize_18, { 0.1,0.2 }, "ScoreText");
		GodModeButton* myGodModeButton = new GodModeButton("Sprites/UI/GodmodeButton.dds", { 960,800 }, { 1,1 }, { 0.5f,0.5f }, "StartButton");
	};


}

