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
        myShop.Disable();

        myPausMenu.Add(myPausMenuBackground);
        myPausMenu.Add(myPausMenuResumeButton);
        myPausMenu.Add(myPausMenuQuitButton);
        myPausMenu.Disable();

        myOptionsMenu.Add(myMasterVolumeSliderText);
        myOptionsMenu.Add(myOptionsMenuBackground);
        myOptionsMenu.Add(myVolumeSlider);
        myOptionsMenu.Add(myMasterVolumeLabelText);
        myOptionsMenu.Add(myVolumeSliderBackground);

        std::string optionsMenuLabel = "Options";
        std::string masterVolumeLabel = "Master Volume";
        myOptionsMenuTitleText->SetText(optionsMenuLabel);
        myMasterVolumeLabelText->SetText(masterVolumeLabel);
        myOptionsMenu.Add(myOptionsMenuTitleText);
        myOptionsMenu.Add(myOptionsMenuReturnButton);
        myOptionsMenu.Disable();

        myPlayer = aPlayer;
        myIsLoading = false;
        myLoadingScreen = new SpriteSheet("Sprites/UI/LoadingScreen.dds");
        myLoadingScreen->SetPosition({ 960, 540 });
        myLoadingScreen->SetLayer(10);
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
        return &myPausMenu;
    }

    MenuObject* MenuManager::GetShop()
    {
        return &myShop;
    }

    MenuObject* MenuManager::GetOptionsMenu()
    {
        return &myOptionsMenu;
    }
 
    void MenuManager::Update()
    {
        myMainMenu.Update();
        myHud.Update();
        myShop.Update();
        myPausMenu.Update();
        myOptionsMenu.Update();
        myLevelSelect->Update();

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
        myShop.Disable();
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
        myMainMenu.Enable();
        myPausMenu.Disable();
        myOptionsMenu.Disable();
        myHud.Disable();
        hasStartedGame = false;
        if (Studio::Timer::GetInstance()->IsFrozen())
        {
            Studio::Timer::GetInstance()->ToggleFreeze();
        }
    }

}
