#include "stdafx.h"
#include "GameWorld.h"
#include <iostream>
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
#include "Player_JsonParser.h"
#include "InputManager.h"
#include "Enums.h"
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
	SAFE_DELETE(myPlayerData);
}

void CGameWorld::Init()
{
	//// Custom Key Bindings
	Studio::InputManager::GetInstance()->BindCustomKeys(Studio::Enums::CustomKey_FlyUp,     { 'W', 38, 'I' });
	Studio::InputManager::GetInstance()->BindCustomKeys(Studio::Enums::CustomKey_FlyDown,   { 'S', 40, 'K' });
	Studio::InputManager::GetInstance()->BindCustomKeys(Studio::Enums::CustomKey_FlyRight,  { 'D', 39, 'L' });
	Studio::InputManager::GetInstance()->BindCustomKeys(Studio::Enums::CustomKey_FlyLeft,   { 'A', 37, 'J' });
	Studio::InputManager::GetInstance()->BindCustomKeys(Studio::Enums::CustomKey_RapidFire, { '1', 'Z' });
	Studio::InputManager::GetInstance()->BindCustomKeys(Studio::Enums::CustomKey_Explosive, { '2', 'X' });
	Studio::InputManager::GetInstance()->BindCustomKeys(Studio::Enums::CustomKey_Shield,    { '3', 'C' });
	Studio::InputManager::GetInstance()->BindCustomKeys(Studio::Enums::CustomKey_Shoot,     { KEY_SPACE });
	Studio::InputManager::GetInstance()->BindCustomKeys(Studio::Enums::CustomKey_Pause,     { KEY_ESCAPE, 'P' });
	//// Example on how to use CustomKeys
	// InputManager::GetInstance()->IsCustomKeyDown(Enums::CustomKey_Explosive)
	//// Or
	// InputManager::GetInstance()->IsCustomKeyDown(Enums::CustomKeys::CustomKey_Explosive)

	myRenderer.Init();
	Studio::AudioManagerAccessor::Construct();
	Studio::RendererAccessor::SetInstance(&myRenderer);
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });
	SAFE_CREATE(myPlayerData, Studio::Player_JsonParser("json/player/player.json"));
	SAFE_CREATE(myPlayer, Studio::Player(myPlayerData));
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

	myBackgroundManager.UpdateBackground(aDeltaTime);

	if (myMenuManager->GameStarted())
	{
		if (myMenuManager->GetGodMode() == true)
		{
			myPlayer->SetGodMode(true);
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
