#include "stdafx.h"
#include "LevelSelect.h"
#include "MenuManager.h"
#include "LevelAccessor.h"

Studio::LevelSelect::LevelSelect(MenuManager* aMenuManager) :
	myMenuManager(aMenuManager)
{
	myLevel1Button = new GenericButton("Sprites/UI/UI_level1.dds", { 360, 400 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	myLevel2Button = new GenericButton("Sprites/UI/UI_level2.dds", { 960, 400 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	myLevel3Button = new GenericButton("Sprites/UI/UI_level3.dds", { 1560, 400 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	printf("Back To Main Menu\n");
	myBackButton = new GenericButton("Sprites/UI/UI_backToMain_text.dds", { 200,900 }, { 1,1 }, { 0.0f,0.5f }, "BackButton", 10);
	myMainMenuBackground = new ImageElement("Sprites/UI/background_maintitle.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 5, "MainMenuBackground");
	myIsActive = false;
	MenuObject::Add(myLevel1Button);
	MenuObject::Add(myLevel2Button);
	MenuObject::Add(myLevel3Button);
	MenuObject::Add(myBackButton);
	MenuObject::Add(myMainMenuBackground);
	MenuObject::Disable();

}

Studio::LevelSelect::~LevelSelect()
{
	SAFE_DELETE(myLevel1Button);
	SAFE_DELETE(myLevel2Button);
	SAFE_DELETE(myLevel3Button);
	SAFE_DELETE(myBackButton);
}

void Studio::LevelSelect::Update()
{
	MenuObject::Update();

	if (myIsActive)
	{
		if (myLevel1Button->IsClicked())
		{
			Studio::LevelAccessor::GetInstance()->LoadLevel(0);
			myMenuManager->StartGame();
			Disable();
		}
		if (myLevel2Button->IsClicked())
		{
			Studio::LevelAccessor::GetInstance()->LoadLevel(1);
			myMenuManager->StartGame();
			Disable();
		}
		if (myLevel3Button->IsClicked())
		{
			Studio::LevelAccessor::GetInstance()->LoadLevel(2);
			myMenuManager->StartGame();
			Disable();
		}
		if (myBackButton->IsClicked())
		{
			MenuObject::Disable();
			myMenuManager->GetMainMenu()->Enable();
			Disable();
		}
	}
}

void Studio::LevelSelect::Enable()
{
	MenuObject::Enable();
	myIsActive = true;
}

void Studio::LevelSelect::Disable()
{
	myIsActive = false;
	MenuObject::Disable();
}


