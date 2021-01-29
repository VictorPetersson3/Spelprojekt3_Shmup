#include "stdafx.h"
#include "GameWorld.h"
#include<iostream>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <tga2d/sprite/sprite.h>
#include "RendererAccessor.h"
#include "LevelManager.h"
#include "MenuManager.h"
#include "CoinAccessor.h"
#include "LevelAccessor.h"
#include "MenuManagerSingleton.h"
#include "ScoreAccessor.h"
#include "AudioManagerAccesor.h"

// Freeze
#include "InputManager.h"
#include "Timer.h"

CGameWorld::CGameWorld()
{
	myTga2dLogoSprite = nullptr;
	myPlayer = nullptr;
}

CGameWorld::~CGameWorld() 
{
	delete myTga2dLogoSprite;
	myTga2dLogoSprite = nullptr;
	SAFE_DELETE(myPlayer);
	SAFE_DELETE(myLevelManager);
	SAFE_DELETE(myMenuManager);
}

void CGameWorld::Init()
{
	myRenderer.Init();
	Studio::AudioManagerAccessor::Construct();
	Studio::RendererAccessor::SetInstance(&myRenderer);
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });
	SAFE_CREATE(myPlayer, Studio::Player("sprites/assets/player/sprites/playerSprite_01.dds"));
	Studio::MenuManagerSingleton::Construct(myPlayer);

	SAFE_CREATE(myCoinManager, Studio::CoinManager());
	Studio::CoinAccessor::SetInstance(myCoinManager);
	SAFE_CREATE(myScoreManager, Studio::ScoreManager());
	Studio::ScoreAccessor::SetInstance(myScoreManager);

	
	myBackgroundManager.CreateTestMapBackground(1920.0f);

	SAFE_CREATE(myLevelManager, Studio::LevelManager());
	myMenuManager = Studio::MenuManagerSingleton::GetInstance();

	Studio::LevelAccessor::SetInstance(myLevelManager);
}

//aIsPlaying is an atomic bool to close the gameplay thread
void CGameWorld::Update(float aDeltaTime, std::atomic<bool>& aIsPlaying)
{
	if (Studio::InputManager::GetInstance()->IsKeyPressed('F'))
	{
		Studio::Timer::GetInstance()->ToggleFreeze();
		if (Studio::Timer::GetInstance()->IsFrozen())
		{
			printf_s("Froze game\n");
		}
		else
		{
			printf_s("Resumed game\n");
		}
	}

	//myBackgroundManager.UpdateBackground(aDeltaTime);

	if (myMenuManager->GameStarted())
	{
		if (myMenuManager->GetGodMode() == true)
		{
			myPlayer->SetGodMode();
		}
		myScoreManager->Update();
		myPlayer->Update();
		myLevelManager->Update(myPlayer);
		myCoinManager->Update();
	}
	
	myMenuManager->Update();
}

void CGameWorld::Render()
{

	//myTga2dLogoSprite->Render();
	myRenderer.Render();
	myMenuManager->Render();

}

void CGameWorld::SwapBuffers()
{
	myRenderer.SwapBuffers();
}
