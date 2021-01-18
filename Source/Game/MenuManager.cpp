#include "stdafx.h"
#include "MenuManager.h"
#include "TestButton.h"

namespace Studio
{
    MenuManager::MenuManager()
    {
        testButton = new TestButton("test", "Sprites/debugpixel.dds", { 0.05f,0.9f }, { 1,1 }, { 0.5f,0.5f });
    }
    MenuManager::~MenuManager()
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
        testButton->Render();
    }
}
