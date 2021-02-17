#pragma once
#include<vector>
#include "macros.h"
#include "MenuObject.h"

namespace Studio
{
	class LevelSelect;
	class Options;
	class LevelManager;
	class ImageElement;
	class TextElement;
	class SliderElement;
	class GenericButton;
	class StartButton;
	class ExitButton;
	class UIElement;
	class ReturnToMainMenuButton;
	class MenuObject;
	class ShopUI;
	class Counter;
	class Player;
	class SpriteSheet;

	class MenuManager
	{
	public:
		MenuManager(Studio::Player* aPlayer);
		~MenuManager();

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

		

		ImageElement* GetShopDescriptionText();

		TextElement* GetShopCostText();
		TextElement* GetShopUpgradeNameText();

		//Jimmikod
		void GreyOutAbilitiesOnCooldown(float aRapidFireCooldown, float aMissileCooldown, float aShieldCooldown);
		void GreyOutAbilitiesDuringTutorial();
	private:

		

		MenuObject myMainMenu;
		MenuObject myHud;
		MenuObject myPauseMenu;
		MenuObject myShop;
		MenuObject myOptionsMenu;
		MenuObject myCreditsMenu;

		Counter* myTutorialCounter;

		ShopUI* myShopUI;

		Studio::Player* myPlayer;

		bool hasStartedGame = false;
		bool inGodMode = false;
		bool myResizeAllElements;
		bool myIsLoading;
		bool myRapidTutorialGrey = true;
		bool myMissileTutorialGrey = true;
		bool myShieldTutorialGrey = true;
		int myLevelToLoad;
		int myTutorialAction;
		SpriteSheet* myLoadingScreen;

#pragma region MainMenu
		StartButton* myStartButton;
		GenericButton* mySettingsButton;
		GenericButton* myCreditsButton;
		ExitButton* myExitButton;
		ImageElement* myMainMenuBackground;
		ImageElement* myMainMenuLogo;

#pragma endregion


		StartButton* myNextLevelButton;

		TextElement* myScoreText;
		TextElement* myCoinText;

		ImageElement* myTestElement;
		ImageElement* myHeart1Element;
		ImageElement* myHeart2Element;
		ImageElement* myHeart3Element;
		ImageElement* myHeart4Element;
		ImageElement* myShopBackground;
		ImageElement* myShopFrames;

		ImageElement* myShopDescriptionText;

		int myRapidCooldown;
		int myMissileCooldown;
		int myShieldCooldown;

		TextElement* myRapidCooldownText;
		TextElement* myMissileCooldownText;
		TextElement* myShieldCooldownText;
		

		ImageElement* myAbilityRapid;
		ImageElement* myAbilityRapidBorder;
		ImageElement* myAbilityMissile;
		ImageElement* myAbilityMissileBorder;
		ImageElement* myAbilityShield;
		ImageElement* myAbilityShieldBorder;




		ImageElement* myOptionsMenuBackground;


		ImageElement* myPausMenuBackground;
		ImageElement* myPausMenuTitle;

		GenericButton* myPausMenuResumeButton;
		ReturnToMainMenuButton* myPausMenuQuitButton;

		TextElement* myShopCoinText;
		TextElement* myShopCostText;
		TextElement* myShopUpgradeNameText;
		

		TextElement* myMasterVolumeSliderText;
		TextElement* myMasterVolumeLabelText;

		TextElement* myOptionsMenuTitleText;
		ImageElement* myVolumeLabel;
		ImageElement* myVolumeBar;

		SliderElement* myVolumeSlider;

		ReturnToMainMenuButton* myOptionsMenuReturnButton;

		GenericButton* myLevelSelectButton;
	
		LevelSelect* myLevelSelect;
		Options* myOptions;

		// Credits
		ImageElement* myCreditsBackground;
		ReturnToMainMenuButton* myCreditsBackButton;
	};


}

