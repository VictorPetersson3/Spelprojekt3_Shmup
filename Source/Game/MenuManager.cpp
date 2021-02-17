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

#define LEVELMANAGER Studio::LevelAccessor::GetInstance()

namespace Studio
{
    Studio::MenuManager::MenuManager(Studio::Player* aPlayer)
    {
        myShopUI = new Studio::ShopUI();
        myLevelSelect = new Studio::LevelSelect(this);
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

        myPlayer = aPlayer;
        myIsLoading = false;
        myLoadingScreen = new SpriteSheet("Sprites/UI/LoadingScreen.dds");
        myLoadingScreen->SetPosition({ 960, 540 });
        myLoadingScreen->SetLayer(10);
        myOptions = new Options(this);
        ResetButtonColliders();
        myTutorialAction = 0;
        myTutorialCounter.SetInterval(17.f);
        
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
        myTutorialCounter.Tick();

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
          

        if (myTutorialCounter.PastInterval())
        {
            if (myTutorialAction == 2)
            {
                myShieldTutorialGrey = false;
            }    

            if (myTutorialAction == 1)
            {
                myTutorialAction = 2;
                myMissileTutorialGrey = false;
                myTutorialCounter.SetInterval(8.f);
            }

            if (myTutorialAction == 0)
            {
                myTutorialAction = 1;
                myRapidTutorialGrey = false;
                myTutorialCounter.SetInterval(7.f);
            }

        }
        
    }

}
