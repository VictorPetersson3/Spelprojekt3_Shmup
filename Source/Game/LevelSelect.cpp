#include "stdafx.h"
#include "LevelSelect.h"
#include "MenuManager.h"
#include "LevelAccessor.h"
#include "GenericButton.h"
#include "ImageElement.h"
#include "UIElement.h"
#include "AudioManagerAccesor.h"

Studio::LevelSelect::LevelSelect(MenuManager* aMenuManager) :
	myMenuManager(aMenuManager)
{
	myLevel1Button = new GenericButton("Sprites/UI/UI_level1.dds", { 360, 400 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	myLevel2Button = new GenericButton("Sprites/UI/UI_level2.dds", { 960, 400 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	myLevel3Button = new GenericButton("Sprites/UI/UI_level3.dds", { 1560, 400 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	myTutorialButton = new GenericButton("Sprites/UI/UI_level3.dds", { 960, 200 }, { 0.8f, 0.8f }, { 0.5f,0.5f }, "LevelButton", 10);
	printf("Back To Main Menu\n");
	myBackButton = new GenericButton("Sprites/UI/UI_backToMain_text.dds", { 400,900 }, { 1,1 }, { 0.5f,0.5f }, "BackButton", 10);
	myMainMenuBackground = new ImageElement("Sprites/UI/background_maintitle.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 5, "MainMenuBackground");
	myIsActive = false;
	MenuObject::Add(myLevel1Button);
	MenuObject::Add(myLevel2Button);
	MenuObject::Add(myLevel3Button);
	MenuObject::Add(myTutorialButton);
	MenuObject::Add(myBackButton);
	MenuObject::Add(myMainMenuBackground);
	MenuObject::Disable();
}

Studio::LevelSelect::~LevelSelect()
{
	SAFE_DELETE(myLevel1Button);
	SAFE_DELETE(myLevel2Button);
	SAFE_DELETE(myLevel3Button);
	SAFE_DELETE(myTutorialButton);
	SAFE_DELETE(myBackButton);
	SAFE_DELETE(myMainMenuBackground);
}

void Studio::LevelSelect::Update()
{
	MenuObject::Update();

	if (myIsActive)
	{
		if (myTutorialButton->IsClicked())
		{
			AudioManagerAccessor::GetInstance()->StopAllSounds();
			AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);
			Studio::LevelAccessor::GetInstance()->LoadLevel(0);
			myMenuManager->StartGame();
			Disable();
		}
		if (myLevel1Button->IsClicked())
		{
			AudioManagerAccessor::GetInstance()->StopAllSounds();
			AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);
			Studio::LevelAccessor::GetInstance()->LoadLevel(1);
			myMenuManager->StartGame();
			Disable();
		}
		if (myLevel2Button->IsClicked())
		{
			AudioManagerAccessor::GetInstance()->StopAllSounds();
			AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);
			Studio::LevelAccessor::GetInstance()->LoadLevel(2);
			myMenuManager->StartGame();
			Disable();
		}
		if (myLevel3Button->IsClicked())
		{
			AudioManagerAccessor::GetInstance()->StopAllSounds();
			AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);
			Studio::LevelAccessor::GetInstance()->LoadLevel(3);
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

void Studio::LevelSelect::RecalcColliders()
{
	myLevel1Button->CalculateButtonCollider();
	myLevel2Button->CalculateButtonCollider();
	myLevel3Button->CalculateButtonCollider();
	myBackButton->CalculateButtonCollider();
}


