#pragma once
#include<vector>
#include "MenuObject.h"
#include "TestButton.h"
#include "UIElement.h"
#include "TextElement.h"
#include "GodModeButton.h"
#include "ImageElement.h"
#include "Player.h"
#include "ShopUI.h"
#include "ShopButton.h"
#include "StartButton.h"

namespace Studio
{
	class MenuManager
	{
	public:
		MenuManager(Studio::Player* aPlayer);
		
		std::vector<UIElement*> myShopButtons;

		MenuObject* GetMainMenu();
		MenuObject* GetHUD();
		MenuObject* GetPauseMenu();
		MenuObject* GetShop();

		void Update();

		void Render();

		bool GameStarted();
		bool GetGodMode();

	private:
		MenuObject myMainMenu;
		MenuObject myHud;
		MenuObject myPausMenu;
		MenuObject myShop;

		ShopUI* myShopUI;

		Studio::Player* myPlayer;

		bool hasStartedGame = false;
		bool inGodMode = false;

		TestButton* myTestButton = new TestButton("Sprites/UI/TempPlayButton.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f },"StartButton");
		StartButton* myStartButton = new StartButton("Sprites/UI/TempPlayButton.dds", { 200,540 }, { 1,1 }, { 0.5f,0.5f }, "PlayButton",10, "");
		StartButton* myNextLevelButton = new StartButton("Sprites/UI/NextLevelButtonTemp.dds", { 960,800 }, { 1,1 }, { 0.5f,0.5f }, "NextLevelButton",10, "");

		TextElement* myScoreText = new TextElement(Tga2D::EFontSize_14, { 0.135,0.117 }, "ScoreText");
		TextElement* myCoinText = new TextElement(Tga2D::EFontSize_14, { 0.11,0.153 }, "CoinText");
		GodModeButton* myGodModeButton = new GodModeButton("Sprites/UI/GodmodeButton.dds", { 960,800 }, { 1,1 }, { 0.5f,0.5f }, "StartButton");
		ImageElement* myTestElement = new ImageElement("Sprites/UI/IGUI/IGUI_Banners.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 2, "HUD");
		ImageElement* myHeart1Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 3,"Heart1");
		ImageElement* myHeart2Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1000,540 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart2");
		ImageElement* myHeart3Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1040,540 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart3");
		ImageElement* myHeart4Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1080,540 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart4");
		ImageElement* myShopBackground = new ImageElement("Sprites/UI/ShopBackground.dds", { 960,540 }, { 10,10 }, { 0.5f,0.5f }, 0, "ShopBackground");

		ImageElement* myPausMenuBackground = new ImageElement("Sprites/UI/TempPausMenuBackground.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 10, "PausMenuBackground");

		TextElement* myShopCoinText = new TextElement(Tga2D::EFontSize_36, { 0.1,0.5 }, "ShopCoinText");
	};


}

