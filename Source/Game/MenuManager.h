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
#include "GenericButton.h"
#include "ExitButton.h"
#include "ReturnToMainMenuButton.h"
#include "SliderElement.h"
#include "GoToMainMenuButton.h"
#include "LevelSelectButton.h"

namespace Studio
{
	class LevelManager;
	class MenuManager
	{
	public:
		MenuManager(Studio::Player* aPlayer);
		
		std::vector<UIElement*> myShopButtons;

		MenuObject* GetMainMenu();
		MenuObject* GetHUD();
		MenuObject* GetPauseMenu();
		MenuObject* GetShop();
		MenuObject* GetOptionsMenu();

		void Update();

		void Render();

		void ResetShop();

		bool GameStarted();
		bool GetGodMode();
		void SetPlayButtonIndex(const int aIndex);
		void SetNextLevelIndex(const int aIndex);
		void Load();

	private:

		MenuObject myMainMenu;
		MenuObject myHud;
		MenuObject myPausMenu;
		MenuObject myShop;
		MenuObject myOptionsMenu;

		ShopUI* myShopUI;

		Studio::Player* myPlayer;

		bool hasStartedGame = false;
		bool inGodMode = false;

		bool myIsLoading;
		int myLevelToLoad;
		SpriteSheet* myLoadingScreen;

		StartButton* myStartButton = new StartButton("Sprites/UI/UI_play.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, "PlayButton",10,false);
		StartButton* myNextLevelButton = new StartButton("Sprites/UI/ShopUI/shopUI_buttons_continue.dds", { 1500,960 }, { 1,1 }, { 0.5f,0.5f }, "NextLevelButton",10,true);
		GenericButton* mySettingsButton = new GenericButton("Sprites/UI/UI_options.dds", { 960,700 }, { 1,1 }, { 0.5f,0.5f }, "OptionsButton", 12);
		GenericButton* myCreditsButton = new GenericButton("Sprites/UI/UI_credits.dds", { 960,860 }, { 1,1 }, { 0.5f,0.5f }, "CreditsButton", 12);
		ExitButton* myExitButton = new ExitButton("Sprites/UI/UI_exit.dds", { 960,1020 }, { 1,1 }, { 0.5f,0.5f }, "ExitButton", 10);

		TextElement* myScoreText = new TextElement(Tga2D::EFontSize_14, { 0.135,0.117 }, "ScoreText");
		TextElement* myCoinText = new TextElement(Tga2D::EFontSize_14, { 0.11,0.153 }, "CoinText");

		ImageElement* myTestElement = new ImageElement("Sprites/UI/IGUI/IGUI_Banners.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 2, "HUD");
		ImageElement* myHeart1Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 3,"Heart1");
		ImageElement* myHeart2Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1000,540 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart2");
		ImageElement* myHeart3Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1040,540 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart3");
		ImageElement* myHeart4Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1080,540 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart4");
		ImageElement* myShopBackground = new ImageElement("Sprites/UI/ShopUI/shopUI_BG.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 0, "ShopBackground");
		ImageElement* myShopFrames = new ImageElement("Sprites/UI/ShopUI/shopUI_frames.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 3, "ShopFrames");


		ImageElement* myMainMenuBackground = new ImageElement("Sprites/UI/background_maintitle.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 5, "MainMenuBackground");


		ImageElement* myOptionsMenuBackground = new ImageElement("Sprites/UI/background_maintitle.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 5, "OptionsMenuBackground");

		ImageElement* myMainMenuLogo = new ImageElement("Sprites/UI/UI_gamelogo.dds", { 960,250 }, { 1,1 }, { 0.5f,0.5f }, 6, "MainMenuBackground");

		ImageElement* myPausMenuBackground = new ImageElement("Sprites/UI/TempPausMenuBackground.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 10, "PausMenuBackground");
		GenericButton* myPausMenuResumeButton = new GenericButton("Sprites/UI/ResumeButtonTemp.dds", { 960,600 }, { 1,1 }, { 0.5f,0.5f }, "ResumeButton", 11);
		ReturnToMainMenuButton* myPausMenuQuitButton = new ReturnToMainMenuButton("Sprites/UI/UI_exit.dds", { 960,800 }, { 1,1 }, { 0.5f,0.5f }, "ExitButton", 11);

		TextElement* myShopCoinText = new TextElement(Tga2D::EFontSize_36, { 0.1,0.5 }, "ShopCoinText");
		TextElement* myMasterVolumeSliderText = new TextElement(Tga2D::EFontSize_30, { 0.64,0.515 }, "myMasterVolumePercentageText");
		TextElement* myMasterVolumeLabelText = new TextElement(Tga2D::EFontSize_36, { 0.42,0.4 }, "myMasterVolumeLabelText");

		TextElement* myOptionsMenuTitleText = new TextElement(Tga2D::EFontSize_48, { 0.45,0.2 }, "OptionsTitle");
		SliderElement* myVolumeSlider = new SliderElement("Sprites/debugpixel.dds", { 960 - 250,540 }, { 500,50 }, 15);
		ImageElement* myVolumeSliderBackground = new ImageElement("Sprites/debugpixel.dds", { 960 - 250,540 }, { 500,50 }, { 0.0f,0.5f }, 14, "VolumeSliderBackground", { 0.3f,0.3f,0.3f,1 });

		GoToMainMenuButton* myOptionsMenuReturnButton = new GoToMainMenuButton("Sprites/UI/UI_exit.dds", { 960,1000 }, { 1,1 }, { 0.5f,0.5f }, "ExitButton", 11);




		LevelSelectButton* myLevelSelectButton = new LevelSelectButton("Sprites/UI/UI_LevelSelect.dds", { 200,540 }, { 1,1 }, { 0.5f,0.5f }, "LevelSelectButton",20);
	};


}

