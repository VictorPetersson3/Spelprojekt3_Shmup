#include "stdafx.h"
#include "MenuManager.h"

namespace Studio
{
    Studio::MenuManager::MenuManager()
    {
        myMainMenu.Add(myTestButton);
        myMainMenu.Add(myScoreText);
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
    }

    bool MenuManager::GameStarted()
    {
        if (!hasStartedGame && myTestButton->myIsClicked == true)
        {
            hasStartedGame = true;
            return myTestButton->myIsClicked;
            myMainMenu.Disable();
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
}
