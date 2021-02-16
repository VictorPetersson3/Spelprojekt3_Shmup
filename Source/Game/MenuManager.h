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
#include "macros.h"

namespace Studio
{
	class LevelSelect;
	class Options;
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
		Options* GetOptions();
		MenuObject* GetCreditsMenu();

		void Update();

		void Render();

		void ResetShop();
		void ResetAllSizes();
		bool GameStarted();
		bool GetGodMode();
		void SetPlayButtonIndex(const int aIndex);
		void SetNextLevelIndex(const int aIndex);
		void Load();
		void StartGame();
		void QuitGameSession();
		void ResetButtonColliders();

		

		//TextElement* GetShopDescriptionText();
		ImageElement* GetShopDescriptionText();

		TextElement* GetShopCostText();
		TextElement* GetShopUpgradeNameText();

		//Jimmikod
		void GreyOutAbilitiesOnCooldown(float aRapidFireCooldown, float aMissileCooldown, float aShieldCooldown);
	private:

		

		MenuObject myMainMenu;
		MenuObject myHud;
		MenuObject myPausMenu;
		MenuObject myShop;
		MenuObject myOptionsMenu;
		MenuObject myCreditsMenu;

		ShopUI* myShopUI;

		Studio::Player* myPlayer;

		bool hasStartedGame = false;
		bool inGodMode = false;
		bool myResizeAllElements;
		bool myIsLoading;
		int myLevelToLoad;
		SpriteSheet* myLoadingScreen;

		StartButton* myStartButton = new StartButton("Sprites/UI/UI_play.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, "PlayButton",10,false);
		StartButton* myNextLevelButton = new StartButton("Sprites/UI/ShopUI/shopUI_buttons_continue.dds", { 1500,960 }, { 1,1 }, { 0.5f,0.5f }, "NextLevelButton",10,true);
		GenericButton* mySettingsButton = new GenericButton("Sprites/UI/UI_options.dds", { 960,700 }, { 1,1 }, { 0.5f,0.5f }, "OptionsButton", 12);
		GenericButton* myCreditsButton = new GenericButton("Sprites/UI/UI_credits.dds", { 960,860 }, { 1,1 }, { 0.5f,0.5f }, "CreditsButton", 12);
		ExitButton* myExitButton = new ExitButton("Sprites/UI/UI_exit.dds", { 960,1020 }, { 1,1 }, { 0.5f,0.5f }, "ExitButton", 10);

		TextElement* myScoreText = new TextElement(Tga2D::EFontSize_18, { 0.17,0.15 }, "ScoreText", Tga2D::CColor({ 1,1,1,1 }), "Text/Beaufort Medium.otf");
		TextElement* myCoinText = new TextElement(Tga2D::EFontSize_18, { 0.14,0.214 }, "CoinText", Tga2D::CColor({ 1,1,1,1 }), "Text/Beaufort Medium.otf");

		ImageElement* myTestElement = new ImageElement("Sprites/UI/UI_playerInfo_captain.dds", { 0,0 }, { 1,1 }, { 0.f,0.f }, 2, "HUD");
		ImageElement* myHeart1Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 990,560 }, { 1,1 }, { 0.5f,0.5f }, 3,"Heart1");
		ImageElement* myHeart2Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1040,560 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart2");
		ImageElement* myHeart3Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1090,560 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart3");
		ImageElement* myHeart4Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1140,560 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart4");
		ImageElement* myShopBackground = new ImageElement("Sprites/UI/ShopUI/shopUI_BG.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 0, "ShopBackground");
		ImageElement* myShopFrames = new ImageElement("Sprites/UI/ShopUI/shopUI_frames.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 3, "ShopFrames");

		ImageElement* myShopDescriptionText = new ImageElement("Sprites/UI/ShopUI/RapidFireAST1.dds", { 1500, 750 }, { 1,1 }, { 0.5f,0.5f }, 60000000, "ShopText");

		int myRapidCooldown;
		int myMissileCooldown;
		int myShieldCooldown;

		TextElement* myRapidCooldownText = new TextElement(Tga2D::EFontSize_36, { 0.375 , 0.91 }, "RapidText", { 1.f, 1.f, 1.f, 1.f }, "Text/Beaufort Medium.otf");
		TextElement* myMissileCooldownText = new TextElement(Tga2D::EFontSize_36, { 0.460  , 0.91 }, "MissileText", { 1.f, 1.f, 1.f, 1.f }, "Text/Beaufort Medium.otf");
		TextElement* myShieldCooldownText = new TextElement(Tga2D::EFontSize_36, { 0.551 , 0.91 }, "ShieldText", { 1.f, 1.f, 1.f, 1.f }, "Text/Beaufort Medium.otf");
		

		ImageElement* myAbilityRapidBorder = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_CooldownFrame.dds", { 790, 990 }, { 1,1 }, { 0.5f,0.5f }, 3, "AbilityRapidBorder");
		ImageElement* myAbilityMissileBorder = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_CooldownFrame.dds", { 960, 990 }, { 1,1 }, { 0.5f,0.5f }, 3, "AbilityMissileBorder");
		ImageElement* myAbilityShieldBorder = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_CooldownFrame.dds", { 1130, 990 }, { 1,1 }, { 0.5f,0.5f }, 3, "AbilityShieldBorder");
		ImageElement* myAbilityRapid = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_RapidFire.dds" , { 790, 990 }, { 1,1 }, { 0.5f,0.5f }, 4, "AbilityRapid");
		ImageElement* myAbilityMissile = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_ExplosiveArsenal.dds" , { 960, 990 }, { 1,1 }, { 0.5f,0.5f }, 4, "AbilityMissile");
		ImageElement* myAbilityShield = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_Shield.dds" , { 1130, 990 }, { 1,1 }, { 0.5f,0.5f }, 4, "AbilityShield");


		ImageElement* myMainMenuBackground = new ImageElement("Sprites/UI/background_maintitle.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 5, "MainMenuBackground");


		ImageElement* myOptionsMenuBackground = new ImageElement("Sprites/UI/background_maintitle.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 5, "OptionsMenuBackground");

		ImageElement* myMainMenuLogo = new ImageElement("Sprites/UI/UI_gamelogo.dds", { 960,250 }, { 1,1 }, { 0.5f,0.5f }, 6, "MainMenuBackground");

		ImageElement* myPausMenuBackground = new ImageElement("Sprites/UI/UI_emptyFrame.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 10, "PausMenuBackground");
		ImageElement* myPausMenuTitle = new ImageElement("Sprites/UI/UI_pause.dds", { 960,275 }, { 1,1 }, { 0.5f,0.5f }, 11, "PausMenuTitle");

		GenericButton* myPausMenuResumeButton = new GenericButton("Sprites/UI/UI_resumeText.dds", { 960,600 }, { 5,5 }, { 0.5f,0.5f }, "ResumeButton", 11);
		ReturnToMainMenuButton* myPausMenuQuitButton = new ReturnToMainMenuButton("Sprites/UI/UI_backToMain_text.dds", { 960,700 }, { 1,1 }, { 0.5f,0.5f }, "ExitButton", 11);

		TextElement* myShopCoinText = new TextElement(Tga2D::EFontSize_36, { 0.56,0.195 }, "ShopCoinText", Tga2D::CColor({1,1,1,1}));
		TextElement* myShopCostText = new TextElement(Tga2D::EFontSize_18, { 0.76f,0.738f }, "ShopCoinCostText", Tga2D::CColor({ 1,1,1,1 }), "Text/Beaufort Medium.otf");
		TextElement* myShopUpgradeNameText = new TextElement(Tga2D::EFontSize_24, { 0.78f,0.645f }, "ShopNameText", Tga2D::CColor({ 1,1,1,1 }),"Text/Beaufort Medium.otf",true);
		

		TextElement* myMasterVolumeSliderText = new TextElement(Tga2D::EFontSize_30, { 0.64,0.104 }, "myMasterVolumePercentageText");
		TextElement* myMasterVolumeLabelText = new TextElement(Tga2D::EFontSize_36, { 0.42,0.104 }, "myMasterVolumeLabelText");

		TextElement* myOptionsMenuTitleText = new TextElement(Tga2D::EFontSize_48, { 0.45,0.2 }, "OptionsTitle");
		SliderElement* myVolumeSlider = new SliderElement("Sprites/debugpixel.dds", { 960 - 250,200 }, { 500,50 }, 15);
		ImageElement* myVolumeSliderBackground = new ImageElement("Sprites/debugpixel.dds", { 960 - 250,200 }, { 500,50 }, { 0.0f,0.5f }, 14, "VolumeSliderBackground", { 0.3f,0.3f,0.3f,1 });

		ReturnToMainMenuButton* myOptionsMenuReturnButton = new ReturnToMainMenuButton("Sprites/UI/UI_exit.dds", { 960,1000 }, { 1,1 }, { 0.5f,0.5f }, "ExitButton", 11);

		GenericButton* myLevelSelectButton = new GenericButton("Sprites/UI/UI_LevelSelect.dds", { 960,100 }, { 1,1 }, { 0.5f,0.5f }, "LevelSelectButton",20);
	
		LevelSelect* myLevelSelect;
		Options* myOptions;

		// Credits
		ImageElement* myCreditsBackground = new ImageElement("Sprites/credits.dds", { 960.0f, 540.0f }, { 1.0f, 1.0f }, { 0.5f, 0.5f }, 20, "CreditsBackground");
		ReturnToMainMenuButton* myCreditsBackButton = new ReturnToMainMenuButton("Sprites/UI/UI_backToMain_text.dds", { 384.0f, 892.0f, }, { 1.0f, 1.0f }, { 0.5f, 0.5f }, "CreditsGoBackButton", 21);
	};


}

