#include "stdafx.h"
#include "Options.h"
#include "MenuManager.h"
#include "Game_Accessor.h"
#include "Timer.h"
#include "ImageElement.h"
#include "GenericButton.h"
#include "UIElement.h"

Studio::Options::Options(MenuManager* aMenuManager)
{
	myMenuManager = aMenuManager;
	myFullscreenText = new ImageElement("Sprites/UI/UI_fullscreen.dds", { 960,400 }, { 1,1 }, { 0.5f,0.5f }, 5, "MainMenuBackground");
	myToggleFullScreenOff = new GenericButton("Sprites/UI/UI_checkBoxOK.dds", { 960, 470 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	myToggleFullScreenOn = new GenericButton("Sprites/UI/UI_checkBox.dds", { 960, 470 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);

	my640x360 = new GenericButton("Sprites/UI/UI_640x360.dds", { 810, 575 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	my960x540 = new GenericButton("Sprites/UI/UI_960x540.dds", { 810, 650 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	my1280x720 = new GenericButton("Sprites/UI/UI_1280x720.dds", { 810, 725 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	my1600x900 = new GenericButton("Sprites/UI/UI_1600x900.dds", { 1110, 575 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	my1920x1080 = new GenericButton("Sprites/UI/UI_1920x1080.dds", { 1110, 650 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	my2560x1440 = new GenericButton("Sprites/UI/UI_2560x1440.dds", { 1110, 725 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);

	myMainMenuBackground = new ImageElement("Sprites/UI/background_maintitle.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 5, "MainMenuBackground");
	myIsActive = false;

	MenuObject::Add(myFullscreenText);
	MenuObject::Add(myToggleFullScreenOn);

	MenuObject::Add(myToggleFullScreenOff);
	MenuObject::Add(my640x360);
	MenuObject::Add(my960x540);
	MenuObject::Add(my1280x720);
	MenuObject::Add(my1600x900);
	MenuObject::Add(my1920x1080);
	MenuObject::Add(my2560x1440);
	MenuObject::Add(myMainMenuBackground);
	MenuObject::Disable();
	myClickTimer = 0;
	myHasStarted = false;
}

Studio::Options::~Options()
{
	SAFE_DELETE(myToggleFullScreenOff);
	SAFE_DELETE(my640x360);
	SAFE_DELETE(my960x540);
	SAFE_DELETE(my1280x720);
	SAFE_DELETE(my1600x900);
	SAFE_DELETE(my1920x1080);
	SAFE_DELETE(my2560x1440);
	SAFE_DELETE(myMainMenuBackground);
}

void Studio::Options::Update()
{
	if (!myHasStarted)
	{
		if (myIsActive)
		{
			Tga2D::Vector2ui res;
			if (myToggleFullScreenOff->IsClicked())
			{
				myToggleFullScreenOff->SetActive(false);
				myToggleFullScreenOn->SetActive(true);
				Studio::GameAccessor::GetInstance().GetGame()->ToggleFullScreen();
				myMenuManager->ResetAllSizes();
				Disable();
			}
			if (myToggleFullScreenOn->IsClicked())
			{
				myToggleFullScreenOff->SetActive(true);
				myToggleFullScreenOn->SetActive(false);
				Studio::GameAccessor::GetInstance().GetGame()->ToggleFullScreen();
				myMenuManager->ResetAllSizes();
				Disable();
			}
			if (myToggleFullScreenOff->IsClicked())
			{
				Studio::GameAccessor::GetInstance().GetGame()->ToggleFullScreen();
				myMenuManager->ResetAllSizes();
				Disable();
			}
			if (!Studio::GameAccessor::GetInstance().GetGame()->GetIsFullscreen())
			{
				if (my640x360->IsClicked())
				{
					res.x = 640;
					res.y = 360;
					Studio::GameAccessor::GetInstance().GetGame()->SetResolution(res);
					myMenuManager->ResetAllSizes();
					Disable();
				}
				if (my960x540->IsClicked())
				{
					res.x = 960;
					res.y = 540;
					Studio::GameAccessor::GetInstance().GetGame()->SetResolution(res);
					myMenuManager->ResetAllSizes();
					Disable();
				}
				if (my1280x720->IsClicked())
				{
					res.x = 1280;
					res.y = 720;
					Studio::GameAccessor::GetInstance().GetGame()->SetResolution(res);
					myMenuManager->ResetAllSizes();
					Disable();
				}
				if (my1600x900->IsClicked())
				{
					res.x = 1600;
					res.y = 900;
					Studio::GameAccessor::GetInstance().GetGame()->SetResolution(res);
					myMenuManager->ResetAllSizes();
					Disable();
				}
				if (my1920x1080->IsClicked())
				{
					res.x = 1920;
					res.y = 1080;
					Studio::GameAccessor::GetInstance().GetGame()->SetResolution(res);
					myMenuManager->ResetAllSizes();
					Disable();
				}
				if (my2560x1440->IsClicked())
				{
					res.x = 2560;
					res.y = 1440;
					Studio::GameAccessor::GetInstance().GetGame()->SetResolution(res);
					myMenuManager->ResetAllSizes();
					Disable();
				}
			}
		}
	}
	else
	{
		myClickTimer += Studio::Timer::GetInstance()->TGetDeltaTime();
	}
	if (myClickTimer > 0.25)
	{
		myHasStarted = true;
	}
	MenuObject::Update();
}

void Studio::Options::Enable()
{
	MenuObject::Enable();
	if (Studio::GameAccessor::GetInstance().GetGame()->GetIsFullscreen())
	{
		myToggleFullScreenOn->SetActive(false);
		my640x360->SetActive(false);
		my960x540->SetActive(false);
		my1280x720->SetActive(false);
		my1600x900->SetActive(false);
		my1920x1080->SetActive(false);
		my2560x1440->SetActive(false);
	}
	else
	{
		myToggleFullScreenOff->SetActive(false);
	}
	myIsActive = true;
	myClickTimer = 0;
}

void Studio::Options::Disable()
{
	myIsActive = false;
	myHasStarted = false;
	MenuObject::Disable();
	myMenuManager->GetOptionsMenu()->Disable();
	myMenuManager->GetMainMenu()->Enable();
}

void Studio::Options::RecalcColliders()
{
	myToggleFullScreenOff->CalculateButtonCollider();
	my640x360->CalculateButtonCollider();
	my960x540->CalculateButtonCollider();
	my1280x720->CalculateButtonCollider();
	my1600x900->CalculateButtonCollider();
	my1920x1080->CalculateButtonCollider();
	my2560x1440->CalculateButtonCollider();
}
