#include "stdafx.h"
#include "MenuManager.h"
#include "Player.h"
#include <iostream>
#include "LevelManager.h"
#include "LevelAccessor.h"
#include "LevelManager.h"

#define LEVELMANAGER Studio::LevelAccessor::GetInstance()

namespace Studio
{
    Studio::MenuManager::MenuManager(Studio::Player* aPlayer)
    {
        myShopUI = new Studio::ShopUI();

        myMainMenu.Add(myGodModeButton);
        myMainMenu.Add(myStartButton);
        myMainMenu.Add(myMainMenuBackground);
        myMainMenu.Add(myMainMenuLogo);
        myMainMenu.Add(mySettingsButton);
        myMainMenu.Add(myCreditsButton);
        myMainMenu.Add(myExitButton);
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
        for (ShopButton* b : myShopUI->GetShopButtons())
        {
            myShop.Add((b));
        }

        myShop.Add(myShopCoinText);
        myShop.Add(myNextLevelButton);
        myShop.Disable();

        myPausMenu.Add(myPausMenuBackground);
        myPausMenu.Add(myPausMenuResumeButton);
        myPausMenu.Disable();

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
 
    void MenuManager::Update()
    {
        myMainMenu.Update();
        myHud.Update();
        myShop.Update();
        myPausMenu.Update();
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
    }

    void MenuManager::Render()
    {
        myScoreText->Render();
        myCoinText->Render();
        myShopCoinText->Render();
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
            return myStartButton->myIsClicked;
        }
        if (!hasStartedGame && myGodModeButton->myIsClicked == true)
        {
            hasStartedGame = true;
            inGodMode = true;
            myMainMenu.Disable();
            myIsLoading = true;
            myHud.Enable();
            myLevelToLoad = LEVELMANAGER->GetCurrentLevelIndex();
            RendererAccessor::GetInstance()->Render(*myLoadingScreen);
            return myGodModeButton->myIsClicked;
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
}
