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
	Studio::RendererAccessor::SetInstance(&myRenderer);
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });
	SAFE_CREATE(myPlayer, Studio::Player(new Tga2D::CSprite("sprites/debugpixel.dds")));
	
	myBackgroundManager.CreateTestMapBackground(5120.f);

	SAFE_CREATE(myLevelManager, Studio::LevelManager());
	SAFE_CREATE(myMenuManager, Studio::MenuManager());
}

//aIsPlaying is an atomic bool to close the gameplay thread
void CGameWorld::Update(float aDeltaTime, std::atomic<bool>& aIsPlaying)
{
	
	myBackgroundManager.UpdateBackground(aDeltaTime);

	myPlayer->Update();
	myLevelManager->Update();
	myMenuManager->Update();
}

void CGameWorld::Render()
{
	myMenuManager->Render();
	//myTga2dLogoSprite->Render();
	myRenderer.Render();
}

void CGameWorld::SwapBuffers()
{
	myRenderer.SwapBuffers();
}


void CGameWorld::CheckIfEnemiesHit()
{
	for (int i = 0; i < myPlayer->GetBullets().size(); i++)
	{
		for (int j = 0; j < myEnemies.size(); j++)
		{
			if (myPlayer->GetBullets()[i]->Intersects(*myEnemies[j]))
			{
				myEnemies.erase(myEnemies.begin() + j);
				break;
			}
		}
	}
}
