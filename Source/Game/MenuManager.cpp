#include "stdafx.h"
#include "MenuManager.h"

namespace Studio
{
    Studio::MenuManager::MenuManager()
    {
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
    void MenuManager::Render()
    {
       // myTestButton.Render();
    }
    void MenuManager::Update()
    {
        //myTestButton.Update();
    }
}
