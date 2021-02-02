#include "stdafx.h"
#include "MenuManager.h"
#include "Player.h"
#include <iostream>

namespace Studio
{
    Studio::MenuManager::MenuManager(Studio::Player* aPlayer)
    {
        myShopUI = new Studio::ShopUI();

        myMainMenu.Add(myTestButton);
        myMainMenu.Add(myGodModeButton);
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

        myShop.Disable();

        myPlayer = aPlayer;
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
        if (!hasStartedGame && myTestButton->myIsClicked == true)
        {
            hasStartedGame = true;
            myMainMenu.Disable();
            myHud.Enable();
            return myTestButton->myIsClicked;

        }
        if (!hasStartedGame && myGodModeButton->myIsClicked == true)
        {
            hasStartedGame = true;
            inGodMode = true;
            myMainMenu.Disable();
            myHud.Enable();
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
}
