#include "stdafx.h"
#include "MenuManager.h"

namespace Studio
{
    Studio::MenuManager::MenuManager()
    {
        myMainMenu.Add(myTestButton);
        myMainMenu.Add(myScoreText);
        myMainMenu.Add(myCoinText);
        myMainMenu.Add(myGodModeButton);
        myMainMenu.Enable();
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
 
    void MenuManager::Update()
    {
        myMainMenu.Update();
    }

    void MenuManager::Render()
    {
        myScoreText->Render();
        myCoinText->Render();
    }

    bool MenuManager::GameStarted()
    {
        if (!hasStartedGame && myTestButton->myIsClicked == true)
        {
            hasStartedGame = true;
            myMainMenu.Disable();
            return myTestButton->myIsClicked;

        }
        if (!hasStartedGame && myGodModeButton->myIsClicked == true)
        {
            hasStartedGame = true;
            inGodMode = true;
            myMainMenu.Disable();
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
