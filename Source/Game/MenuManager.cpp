#include "stdafx.h"
#include "MenuManager.h"
#include "Player.h"
#include <iostream>
#include "LevelManager.h"
#include "LevelAccessor.h"
#include "LevelManager.h"
#include <string>
#include "InputManager.h"
#include "LevelSelect.h"
#include "Timer.h"
#include "Options.h"
#include "PlayerAccessor.h"
#include "Player_JsonParser.h"
#include "tga2d/sprite/sprite.h"
#include "AudioManager.h"
#include "AudioManagerAccesor.h"
#include "ImageElement.h"
#include "TextElement.h"
#include "SliderElement.h"
#include "GenericButton.h"
#include "StartButton.h"
#include "ExitButton.h"
#include "UIElement.h"
#include "ReturnToMainMenuButton.h"
#include "ShopUI.h"
#include "Counter.h"
#include "MenuObject.h"
#include "SpriteSheet.h"

#define LEVELMANAGER Studio::LevelAccessor::GetInstance()

namespace Studio
{
    Studio::MenuManager::MenuManager(Studio::Player* aPlayer)
    {
#pragma region Declarations
        myTestElement = new ImageElement("Sprites/UI/UI_playerInfo_captain.dds", { 0,0 }, { 1,1 }, { 0.f,0.f }, 2, "HUD");
        myHeart1Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 990,560 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart1");
        myHeart2Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1040,560 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart2");
        myHeart3Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1090,560 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart3");
        myHeart4Element = new ImageElement("Sprites/UI/IGUI/IGUI_Heart.dds", { 1140,560 }, { 1,1 }, { 0.5f,0.5f }, 3, "Heart4");
        myShopBackground = new ImageElement("Sprites/UI/ShopUI/shopUI_BG.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 0, "ShopBackground");
        myShopFrames = new ImageElement("Sprites/UI/ShopUI/shopUI_frames.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 3, "ShopFrames");
        myShopDescriptionText = new ImageElement("Sprites/UI/ShopUI/RapidFireAST1.dds", { 1500, 750 }, { 1,1 }, { 0.5f,0.5f }, 60000000, "ShopText");

        myAbilityRapid = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_RapidFire.dds", { 150, 400 }, { 1,1 }, { 0.5f,0.5f }, 4, "AbilityRapid");
        myAbilityRapidBorder = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_CooldownFrame.dds", { 150, 400 }, { 1,1 }, { 0.5f,0.5f }, 3, "AbilityRapidBorder");
        myAbilityMissile = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_ExplosiveArsenal.dds", { 150, 550 }, { 1,1 }, { 0.5f,0.5f }, 4, "AbilityMissile");
        myAbilityMissileBorder = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_CooldownFrame.dds", { 150, 550 }, { 1,1 }, { 0.5f,0.5f }, 3, "AbilityMissileBorder");
        myAbilityShield = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_Shield.dds", { 150, 700 }, { 1,1 }, { 0.5f,0.5f }, 4, "AbilityShield");
        myAbilityShieldBorder = new ImageElement("Sprites/UI/IGUI/IGUI_Abilities_CooldownFrame.dds", { 150, 700 }, { 1,1 }, { 0.5f,0.5f }, 3, "AbilityShieldBorder");

        myMainMenuBackground = new ImageElement("Sprites/UI/background_maintitle.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 5, "MainMenuBackground");
        myOptionsMenuBackground = new ImageElement("Sprites/UI/background_maintitle.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 5, "OptionsMenuBackground");
        myMainMenuLogo = new ImageElement("Sprites/UI/UI_gamelogo.dds", { 960,250 }, { 1,1 }, { 0.5f,0.5f }, 6, "MainMenuBackground");

        myPausMenuBackground = new ImageElement("Sprites/UI/UI_emptyFrame.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 10, "PausMenuBackground");
        myPausMenuTitle = new ImageElement("Sprites/UI/UI_pause.dds", { 960,275 }, { 1,1 }, { 0.5f,0.5f }, 11, "PausMenuTitle");

        myVolumeLabel = new ImageElement("Sprites/UI/UI_volume.dds", { 960,160 }, { 1,1 }, { 0.5f,0.5f }, 50, "volumeSliderLabel");
        myVolumeBar = new ImageElement("Sprites/UI/UI_volumeSliderBar.dds", { 960,250 }, { 1,1 }, { 0.5f,0.5f }, 50, "volumeSliderLabel");

        myCreditsBackground = new ImageElement("Sprites/credits.dds", { 960.0f, 540.0f }, { 1.0f, 1.0f }, { 0.5f, 0.5f }, 20, "CreditsBackground");


        myScoreText = new TextElement(Tga2D::EFontSize_18, { 0.17,0.15 }, "ScoreText", Tga2D::CColor({ 1,1,1,1 }), "Text/Beaufort Medium.otf");
        myCoinText = new TextElement(Tga2D::EFontSize_18, { 0.14,0.214 }, "CoinText", Tga2D::CColor({ 1,1,1,1 }), "Text/Beaufort Medium.otf");

        myRapidCooldownText = new TextElement(Tga2D::EFontSize_36, { 0.04 , 0.360 }, "RapidText", { 1.f, 1.f, 1.f, 1.f }, "Text/Beaufort Medium.otf");
        myMissileCooldownText = new TextElement(Tga2D::EFontSize_36, { 0.04  , 0.499 }, "MissileText", { 1.f, 1.f, 1.f, 1.f }, "Text/Beaufort Medium.otf");
        myShieldCooldownText = new TextElement(Tga2D::EFontSize_36, { 0.04 , 0.638 }, "ShieldText", { 1.f, 1.f, 1.f, 1.f }, "Text/Beaufort Medium.otf");

        myShopCoinText = new TextElement(Tga2D::EFontSize_36, { 0.56,0.195 }, "ShopCoinText", Tga2D::CColor({ 1,1,1,1 }));
        myShopCostText = new TextElement(Tga2D::EFontSize_18, { 0.76f,0.738f }, "ShopCoinCostText", Tga2D::CColor({ 1,1,1,1 }), "Text/Beaufort Medium.otf");
        myShopUpgradeNameText = new TextElement(Tga2D::EFontSize_24, { 0.78f,0.645f }, "ShopNameText", Tga2D::CColor({ 1,1,1,1 }), "Text/Beaufort Medium.otf", true);

        myMasterVolumeSliderText = new TextElement(Tga2D::EFontSize_30, { 0.64,0.24 }, "myMasterVolumePercentageText", Tga2D::CColor({ 1,1,1,1 }), "Text/Beaufort Medium.otf");
        myMasterVolumeLabelText = new TextElement(Tga2D::EFontSize_36, { 0.42,0.104 }, "myMasterVolumeLabelText");

        myOptionsMenuTitleText = new TextElement(Tga2D::EFontSize_48, { 0.45,0.25 }, "OptionsTitle");

        myVolumeSlider = new SliderElement("Sprites/debugpixel.dds", { 960 - 185,250 }, { 370,50 }, 15);

        mySettingsButton = new GenericButton("Sprites/UI/UI_options.dds", { 960,780 }, { 0.9f,0.9f }, { 0.5f,0.5f }, "OptionsButton", 12);
        myCreditsButton = new GenericButton("Sprites/UI/UI_credits.dds", { 960,900 }, { 0.9f,0.9f }, { 0.5f,0.5f }, "CreditsButton", 12);

        myPausMenuResumeButton = new GenericButton("Sprites/UI/UI_resumeText.dds", { 960,600 }, { 5,5 }, { 0.5f,0.5f }, "ResumeButton", 11);
        myLevelSelectButton = new GenericButton("Sprites/UI/UI_LevelSelect.dds", { 960,660 }, { 0.9f,0.9f }, { 0.5f,0.5f }, "LevelSelectButton", 20);

        myStartButton = new StartButton("Sprites/UI/UI_play.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, "PlayButton", 10, false);
        myNextLevelButton = new StartButton("Sprites/UI/ShopUI/shopUI_buttons_continue.dds", { 1500,960 }, { 1,1 }, { 0.5f,0.5f }, "NextLevelButton", 10, true);

        myExitButton = new ExitButton("Sprites/UI/UI_exit.dds", { 960,1020 }, { 0.9f,0.9f }, { 0.5f,0.5f }, "ExitButton", 10);

        myPausMenuQuitButton = new ReturnToMainMenuButton("Sprites/UI/UI_backToMain_text.dds", { 960,700 }, { 1,1 }, { 0.5f,0.5f }, "ExitButton", 11);
        myOptionsMenuReturnButton = new ReturnToMainMenuButton("Sprites/UI/UI_exit.dds", { 960,1000 }, { 1,1 }, { 0.5f,0.5f }, "ExitButton", 11);
        myCreditsBackButton = new ReturnToMainMenuButton("Sprites/UI/UI_backToMain_text.dds", { 384.0f, 892.0f, }, { 1.0f, 1.0f }, { 0.5f, 0.5f }, "CreditsGoBackButton", 21);

        myShopUI = new Studio::ShopUI();
        myLevelSelect = new Studio::LevelSelect(this);
        myTutorialCounter = new Studio::Counter();
        myOptions = new Options(this);

#pragma endregion

#pragma region AddMenuObjects

        myMainMenu.Add(myStartButton);
        myMainMenu.Add(myMainMenuBackground);
        myMainMenu.Add(myMainMenuLogo);
        myMainMenu.Add(mySettingsButton);
        myMainMenu.Add(myCreditsButton);
        myMainMenu.Add(myExitButton);
        myMainMenu.Add(myLevelSelectButton);
        myMainMenu.Enable();

        myHud.Add(myTestElement);
        myHud.Add(myHeart1Element);
        myHud.Add(myHeart2Element);
        myHud.Add(myHeart3Element);
        myHud.Add(myHeart4Element);
        myHud.Add(myAbilityRapidBorder);
        myHud.Add(myAbilityMissileBorder);
        myHud.Add(myAbilityShieldBorder);
        myHud.Add(myAbilityRapid);
        myHud.Add(myAbilityMissile);
        myHud.Add(myAbilityShield);
        myHud.Add(myRapidCooldownText);
        myHud.Add(myMissileCooldownText);
        myHud.Add(myShieldCooldownText);
        myHud.Add(myScoreText);
        myHud.Add(myCoinText);
        myHud.Disable();

        myShop.Add(myShopBackground);
        for (ButtonElement* b : myShopUI->GetShopButtons())
        {
            myShop.Add((b));
        }

        myShop.Add(myShopCoinText);
        myShop.Add(myNextLevelButton);
        myShop.Add(myShopFrames);
        myShop.Add(myShopDescriptionText);
        myShop.Add(myShopCostText);
        myShop.Add(myShopUpgradeNameText);
        myShop.Disable();

        myPauseMenu.Add(myPausMenuBackground);
        myPauseMenu.Add(myPausMenuTitle);
        myPauseMenu.Add(myPausMenuResumeButton);
        myPauseMenu.Add(myPausMenuQuitButton);
        myPauseMenu.Disable();

        myOptionsMenu.Add(myMasterVolumeSliderText);
        myOptionsMenu.Add(myOptionsMenuBackground);
        myOptionsMenu.Add(myVolumeSlider);
        myOptionsMenu.Add(myMasterVolumeLabelText);

        // Credits
        myCreditsMenu.Add(myCreditsBackground);
        myCreditsMenu.Add(myCreditsBackButton);

        std::string optionsMenuLabel = "Options";
        std::string masterVolumeLabel = "Master Volume";
        myOptionsMenuTitleText->SetText(optionsMenuLabel);
        myMasterVolumeLabelText->SetText(masterVolumeLabel);
        myOptionsMenu.Add(myOptionsMenuTitleText);
        myOptionsMenu.Add(myOptionsMenuReturnButton);
        myOptionsMenu.Add(myVolumeLabel);
        myOptionsMenu.Add(myVolumeBar);
        myOptionsMenu.Disable();

#pragma endregion


        myPlayer = aPlayer;
        myIsLoading = false;
        myLoadingScreen = new SpriteSheet("Sprites/UI/LoadingScreen.dds");
        myLoadingScreen->SetPosition({ 960, 540 });
        myLoadingScreen->SetLayer(10);
        ResetButtonColliders();
        myTutorialAction = 0;
        myTutorialCounter->SetInterval(17.f);
        
    }

    MenuManager::~MenuManager()
    {
        SAFE_DELETE(myLoadingScreen);
        SAFE_DELETE(myStartButton);
        SAFE_DELETE(myNextLevelButton);
        SAFE_DELETE(mySettingsButton);
        SAFE_DELETE(myCreditsButton);
        SAFE_DELETE(myExitButton);
        SAFE_DELETE(myScoreText);
        SAFE_DELETE(myCoinText);
        SAFE_DELETE(myTestElement);
        SAFE_DELETE(myHeart1Element);
        SAFE_DELETE(myHeart2Element);
        SAFE_DELETE(myHeart3Element);
        SAFE_DELETE(myHeart4Element);
        SAFE_DELETE(myShopBackground);
        SAFE_DELETE(myShopFrames);
        SAFE_DELETE(myShopDescriptionText);
        SAFE_DELETE(myRapidCooldownText);
        SAFE_DELETE(myMissileCooldownText);
        SAFE_DELETE(myShieldCooldownText);
        SAFE_DELETE(myAbilityRapidBorder);
        SAFE_DELETE(myAbilityMissileBorder);
        SAFE_DELETE(myAbilityShieldBorder);
        SAFE_DELETE(myAbilityRapid);
        SAFE_DELETE(myAbilityMissile);
        SAFE_DELETE(myAbilityShield);
        SAFE_DELETE(myMainMenuBackground);
        SAFE_DELETE(myOptionsMenuBackground);
        SAFE_DELETE(myMainMenuLogo);
        SAFE_DELETE(myPausMenuBackground);
        SAFE_DELETE(myPausMenuTitle);
        SAFE_DELETE(myPausMenuResumeButton);
        SAFE_DELETE(myPausMenuQuitButton);
        SAFE_DELETE(myShopCoinText);
        SAFE_DELETE(myShopCostText);
        SAFE_DELETE(myShopUpgradeNameText);
        SAFE_DELETE(myMasterVolumeSliderText);
        SAFE_DELETE(myMasterVolumeLabelText);
        SAFE_DELETE(myOptionsMenuTitleText);
        SAFE_DELETE(myVolumeLabel);
        SAFE_DELETE(myVolumeBar);
        SAFE_DELETE(myVolumeSlider);
        SAFE_DELETE(myOptionsMenuReturnButton);
        SAFE_DELETE(myLevelSelectButton);
        SAFE_DELETE(myLevelSelect);
        SAFE_DELETE(myOptions);
        SAFE_DELETE(myCreditsBackground);
        SAFE_DELETE(myCreditsBackButton);
        SAFE_DELETE(myTutorialCounter);
    }              

    MenuObject* Studio::MenuManager::GetMainMenu()
    {
        return &myMainMenu;
    }

    MenuObject* Studio::MenuManager::GetHUD()
    {
        return &myHud;
    }

    MenuObject* Studio::MenuManager::GetPauseMenu()
    {
        return &myPauseMenu;
    }

    MenuObject* MenuManager::GetShop()
    {
        return &myShop;
    }

    MenuObject* MenuManager::GetOptionsMenu()
    {
        return &myOptionsMenu;
    }

    Options* MenuManager::GetOptions()
    {
        return myOptions;
    }
    MenuObject* MenuManager::GetCreditsMenu()
    {
        return &myCreditsMenu;
    }
 
    void MenuManager::Update()
    {
        
        ResetButtonColliders();
        if (myResizeAllElements)
        {
            myResizeAllElements = false;
        }
        myMainMenu.Update();
        myHud.Update();
        myShop.Update();
        myPauseMenu.Update();
        myOptionsMenu.Update();
        myLevelSelect->Update();
        myOptions->Update();

        myCreditsMenu.Update();

        if (myCreditsButton->IsClicked())
        {
            myMainMenu.Disable();
            myCreditsMenu.Enable();
        }
        

        if (myIsLoading && hasStartedGame)
        {
            RendererAccessor::GetInstance()->Render(*myLoadingScreen);
        }
        if (myPlayer->GetCurrentHealth() == myPlayer->GetMaxHealth() && hasStartedGame)
        {
            myHud.GetElementWithTag("Heart4")->SetActive(true);
            myHud.GetElementWithTag("Heart3")->SetActive(true);
            myHud.GetElementWithTag("Heart2")->SetActive(true);
            myHud.GetElementWithTag("Heart1")->SetActive(true);
        }
        if (myPlayer->GetCurrentHealth() == 3)
        {
            myHud.GetElementWithTag("Heart4")->SetActive(false);
        }
        else if (myPlayer->GetCurrentHealth() == 2)
        {
            myHud.GetElementWithTag("Heart3")->SetActive(false);
        }
        else if (myPlayer->GetCurrentHealth() == 1)
        {
            myHud.GetElementWithTag("Heart2")->SetActive(false);
        }
        else if (myPlayer->GetCurrentHealth() == 0)
        {
            myHud.GetElementWithTag("Heart1")->SetActive(false);
        }

        if (mySettingsButton->IsClicked())
        {
            myMainMenu.Disable();
            myOptionsMenu.Enable();
            myOptions->Enable();
            mySettingsButton->SetActive(false);
        }
        if (myLevelSelectButton->IsClicked())
        {
            myLevelSelect->Enable();
            myMainMenu.Disable();
        }
        if (myExitButton->IsClicked())
        {
            Tga2D::CEngine::GetInstance()->Shutdown();
        }

        if (myNextLevelButton->IsClicked())
        {
            ResetShop();
            myShopDescriptionText->SetActive(false);
            myNextLevelButton->SetActive(false);
            AudioManagerAccessor::GetInstance()->StopSound("Audio/PiratesOfTheBaltic_-_TheBootyMerchant.mp3");
        }

        if (Studio::InputManager::GetInstance()->IsKeyPressed('N'))
        {
            myNextLevelButton->OnClick();
            ResetShop();
            myNextLevelButton->SetActive(false);
        }

        myMasterVolumeSliderText->SetText(std::to_string( static_cast<int>(myVolumeSlider->fillPercentage * 100)));
    }

    void MenuManager::Render()
    {
        myScoreText->Render();
        myCoinText->Render();
        myShopCoinText->Render();
        myOptionsMenuTitleText->Render();
        myMasterVolumeSliderText->Render();
        myMasterVolumeLabelText->Render();
        myShopUpgradeNameText->Render();
        if (myRapidCooldown > 0)
            myRapidCooldownText->Render();
        if (myMissileCooldown > 0)
            myMissileCooldownText->Render();
        if (myShieldCooldown > 0)
            myShieldCooldownText->Render();
        myShopCostText->Render();

    }

    void MenuManager::ResetShop()
    {
        myShopUI->ResetButtons();

        myShop.Clear();
        myShop.Add(myShopBackground);
        for (ButtonElement* b : myShopUI->GetShopButtons())
        {
            myShop.Add((b));
        }
        myShop.Add(myShopFrames);
        myShop.Add(myShopCoinText);
        myShop.Add(myNextLevelButton);
        myShop.Add(myShopCostText);
        myShop.Add(myShopUpgradeNameText);
        myShop.Disable();
    }

    void MenuManager::ResetAllSizes()
    {
        myResizeAllElements = true;
    }

    bool MenuManager::GameStarted()
    {
        if (!hasStartedGame && myStartButton->myIsClicked == true)
        {
            hasStartedGame = true;
            myMainMenu.Disable();
            myHud.Enable();
            myIsLoading = true;
            myLevelToLoad = LEVELMANAGER->GetCurrentLevelIndex();
            RendererAccessor::GetInstance()->Render(*myLoadingScreen);
            Load();
            return myStartButton->myIsClicked;
        }
        else if(hasStartedGame)
        {
            return true;
        }
        else
        {
            return false;
        }            
    }
    bool MenuManager::GetGodMode()
    {
        return inGodMode;
    }
  
    void MenuManager::SetPlayButtonIndex(const int aIndex)
    {
        myStartButton->SetLevelToLoad(aIndex);
    }
    void MenuManager::SetNextLevelIndex(const int aIndex)
    {
        myNextLevelButton->SetLevelToLoad(aIndex);
    }
    void MenuManager::Load()
    {
        if (myIsLoading)
        {
            myIsLoading = false;
            LEVELMANAGER->LoadLevel(myLevelToLoad);
        }
    }
    void MenuManager::StartGame()
    {
        hasStartedGame = true;
        myHud.Enable();
        myMainMenu.Disable();
        if (Studio::Timer::GetInstance()->IsFrozen())
        {
            Studio::Timer::GetInstance()->ToggleFreeze();
        }
    }

    void MenuManager::QuitGameSession()
    {
        myOptions->Disable();
        myOptionsMenu.Disable();
        myMainMenu.Enable();
        myPauseMenu.Disable();
        myOptionsMenu.Disable();
        myHud.Disable();
        myCreditsMenu.Disable();
        myShop.Disable();
        hasStartedGame = false;
        myStartButton->myIsClicked = false;
        Studio::AudioManagerAccessor::GetInstance()->Play2D("Audio/MainTheme.mp3", true, 0.15f);
        if (Studio::Timer::GetInstance()->IsFrozen())
        {
            Studio::Timer::GetInstance()->ToggleFreeze();
        }
    }

    void MenuManager::ResetButtonColliders()
    {
        myStartButton->CalculateButtonCollider();
        myNextLevelButton->CalculateButtonCollider();
        mySettingsButton->CalculateButtonCollider();
        myCreditsButton->CalculateButtonCollider();
        myExitButton->CalculateButtonCollider();

        myPausMenuResumeButton->CalculateButtonCollider();
        myPausMenuQuitButton->CalculateButtonCollider();
        myOptionsMenuReturnButton->CalculateButtonCollider();
        myLevelSelectButton->CalculateButtonCollider();
        myOptions->RecalcColliders();
        myLevelSelect->RecalcColliders();
    }

    ImageElement* MenuManager::GetShopDescriptionText()
    {
        return myShopDescriptionText;
    }

    TextElement* MenuManager::GetShopCostText()
    {
        return myShopCostText;
    }

    TextElement* MenuManager::GetShopUpgradeNameText()
    {
        return(myShopUpgradeNameText);
    }

    void MenuManager::GreyOutAbilitiesOnCooldown(float aRapidFireCooldown, float aMissileCooldown, float aShieldCooldown)
    {
        
        myRapidCooldown = aRapidFireCooldown;
        myMissileCooldown = aMissileCooldown;
        myShieldCooldown = aShieldCooldown;

        if (aRapidFireCooldown > 0.f)
        {
            
            myAbilityRapid->GetSpriteSheet()->GetSprite()->SetColor({ 1.f, 1.f, 1.f, 0.5f });
            myRapidCooldownText->SetText(std::to_string(myRapidCooldown));

        }
        else
        {
            myAbilityRapid->GetSpriteSheet()->GetSprite()->SetColor({ 1.f, 1.f, 1.f, 1.f });
        }

        if (aMissileCooldown > 0.f)
        {
            myAbilityMissile->GetSpriteSheet()->GetSprite()->SetColor({ 1.f, 1.f, 1.f, 0.5f });
            myMissileCooldownText->SetText(std::to_string(myMissileCooldown));
        }
        else
        {
            myAbilityMissile->GetSpriteSheet()->GetSprite()->SetColor({ 1.f, 1.f, 1.f, 1.f });
        }

        if (aShieldCooldown > 0.f)
        {
            myAbilityShield->GetSpriteSheet()->GetSprite()->SetColor({ 1.f, 1.f, 1.f, 0.5f });
            myShieldCooldownText->SetText(std::to_string(myShieldCooldown));
        }

        else
        {
            myAbilityShield->GetSpriteSheet()->GetSprite()->SetColor({ 1.f, 1.f, 1.f, 1.f });

        }

        if (LevelAccessor::GetInstance()->GetCurrentLevelIndex() == 0)
        {
            GreyOutAbilitiesDuringTutorial();
        }
    }
        
    

    void MenuManager::GreyOutAbilitiesDuringTutorial()
    {
        myTutorialCounter->Tick();

        if (myRapidTutorialGrey)
        {
            myAbilityRapid->GetSpriteSheet()->GetSprite()->SetColor({ 1.f, 1.f, 1.f, 0.1f });
        }
        if (myMissileTutorialGrey)
        {
            myAbilityMissile->GetSpriteSheet()->GetSprite()->SetColor({ 1.f, 1.f, 1.f, 0.1f });
        }
        if (myShieldTutorialGrey)
        {
            myAbilityShield->GetSpriteSheet()->GetSprite()->SetColor({ 1.f, 1.f, 1.f, 0.1f });
        }
          

        if (myTutorialCounter->PastInterval())
        {
            if (myTutorialAction == 2)
            {
                myShieldTutorialGrey = false;
            }    

            if (myTutorialAction == 1)
            {
                myTutorialAction = 2;
                myMissileTutorialGrey = false;
                myTutorialCounter->SetInterval(8.f);
            }

            if (myTutorialAction == 0)
            {
                myTutorialAction = 1;
                myRapidTutorialGrey = false;
                myTutorialCounter->SetInterval(7.f);
            }

        }
        
    }

}
