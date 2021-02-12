#include "stdafx.h"
#include "Options.h"
#include "MenuManager.h"
#include "Game_Accessor.h"
#include "Timer.h"
Studio::Options::Options(MenuManager* aMenuManager)
{
	myMenuManager = aMenuManager;
	myToggleFullScreen = new GenericButton("Sprites/UI/UI_level1.dds", { 1300, 100 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	my640x360 = new GenericButton("Sprites/UI/UI_level2.dds", { 1300, 250 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	my960x540 = new GenericButton("Sprites/UI/UI_level3.dds", { 1300, 400 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	my1280x720 = new GenericButton("Sprites/UI/UI_level3.dds", { 1300, 550 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	my1600x900 = new GenericButton("Sprites/UI/UI_level3.dds", { 1300, 700 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	my1920x1080 = new GenericButton("Sprites/UI/UI_level3.dds", { 1300, 850 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	my2560x1440 = new GenericButton("Sprites/UI/UI_level3.dds", { 1300, 1000 }, { 1,1 }, { 0.5f,0.5f }, "LevelButton", 10);
	myMainMenuBackground = new ImageElement("Sprites/UI/background_maintitle.dds", { 960,540 }, { 1,1 }, { 0.5f,0.5f }, 5, "MainMenuBackground");
	myIsActive = false;

	MenuObject::Add(myToggleFullScreen);
	MenuObject::Add(my640x360);
	MenuObject::Add(my960x540);
	MenuObject::Add(my1280x720);
	MenuObject::Add(my1600x900);
	MenuObject::Add(my1920x1080);
	MenuObject::Add(my2560x1440);
	MenuObject::Add(myMainMenuBackground);
	MenuObject::Disable();
	myClickTimer = 0;
}

Studio::Options::~Options()
{
	SAFE_DELETE(myToggleFullScreen);
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
	myClickTimer += Studio::Timer::GetInstance()->TGetDeltaTime();
	if (myIsActive)
	{
		Tga2D::Vector2ui res;

		if (myToggleFullScreen->IsClicked())
		{
			Studio::GameAccessor::GetInstance().GetGame()->ToggleFullScreen();
			myMenuManager->ResetAllSizes();
			myClickTimer = 0;
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
				myClickTimer = 0;
				Disable();
			}
			if (my960x540->IsClicked())
			{
				res.x = 960;
				res.y = 540;
				Studio::GameAccessor::GetInstance().GetGame()->SetResolution(res);
				myMenuManager->ResetAllSizes();
				myClickTimer = 0;
				Disable();
			}
			if (my1280x720->IsClicked())
			{
				res.x = 1280;
				res.y = 720;
				Studio::GameAccessor::GetInstance().GetGame()->SetResolution(res);
				myMenuManager->ResetAllSizes();
				myClickTimer = 0;
				Disable();
			}
			if (my1600x900->IsClicked())
			{
				res.x = 1600;
				res.y = 900;
				Studio::GameAccessor::GetInstance().GetGame()->SetResolution(res);
				myMenuManager->ResetAllSizes();
				myClickTimer = 0;
				Disable();
			}
			if (my1920x1080->IsClicked())
			{
				res.x = 1920;
				res.y = 1080;
				Studio::GameAccessor::GetInstance().GetGame()->SetResolution(res);
				myMenuManager->ResetAllSizes();
				myClickTimer = 0;
				Disable();
			}
			if (my2560x1440->IsClicked())
			{
				res.x = 2560;
				res.y = 1440;
				Studio::GameAccessor::GetInstance().GetGame()->SetResolution(res);
				myMenuManager->ResetAllSizes();
				myClickTimer = 0;
				Disable();
			}
		}
	}
	MenuObject::Update();
}

void Studio::Options::Enable()
{
	MenuObject::Enable();
	myIsActive = true;
}

void Studio::Options::Disable()
{
	myIsActive = false;
	MenuObject::Disable();
	myMenuManager->GetOptionsMenu()->Disable();
	myMenuManager->GetMainMenu()->Enable();
}

void Studio::Options::RecalcColliders()
{
	myToggleFullScreen->CalculateButtonCollider();
	my640x360->CalculateButtonCollider();
	my960x540->CalculateButtonCollider();
	my1280x720->CalculateButtonCollider();
	my1600x900->CalculateButtonCollider();
	my1920x1080->CalculateButtonCollider();
	my2560x1440->CalculateButtonCollider();
}
