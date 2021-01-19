#include "stdafx.h"
#include "GameWorld.h"
#include<iostream>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <tga2d/sprite/sprite.h>
#include "RendererAccessor.h"
#include "LevelManager.h"

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
}

void CGameWorld::Init()
{
	myRenderer.Init();
	Studio::RendererAccessor::SetInstance(&myRenderer);
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });
	SAFE_CREATE(myPlayer, Studio::Player(new Tga2D::CSprite("sprites/debugpixel.dds")));
	
	for (int i = 0; i < 1; i++)
	{
		auto enemy = new Studio::Enemy(new Tga2D::CSprite("sprites/debugpixel.dds"), { 1500, 540 });
		myEnemies.push_back(enemy);
	}
	myBackgroundManager.CreateTestMapBackground(5120.f);

	SAFE_CREATE(myLevelManager, Studio::LevelManager());
}

//aIsPlaying is an atomic bool to close the gameplay thread
void CGameWorld::Update(float aDeltaTime, std::atomic<bool>& aIsPlaying)
{
	UpdatePlayer(aDeltaTime);

	UpdateEnemies(aDeltaTime);

	CheckIfEnemiesHit();
	
	myBackgroundManager.UpdateBackground(aDeltaTime);

	myLevelManager->Update();
}

void CGameWorld::Render()
{
	//myTga2dLogoSprite->Render();
	myRenderer.Render();
}

void CGameWorld::SwapBuffers()
{
	myRenderer.SwapBuffers();
}

void CGameWorld::UpdatePlayer(float aDeltaTime)
{
	//Uppdaterar och renderar ut spelaren samt dess kulor.
	myPlayer->Update(aDeltaTime);
	Studio::RendererAccessor::GetInstance()->Render(*myPlayer);
	for (int i = 0; i < myPlayer->GetBullets().size(); i++)
	{
		Studio::RendererAccessor::GetInstance()->Render(*myPlayer->GetBullets()[i]);
	}
}

void CGameWorld::UpdateEnemies(float aDeltaTime)
{
	//Uppdaterar Enemies, Renderar ut dem, samt renderar ut Enemies kulor
	for (int i = 0; i < myEnemies.size(); i++)
	{
		myEnemies[i]->Update(aDeltaTime);
		Studio::RendererAccessor::GetInstance()->Render(*myEnemies[i]);
		for (int j = 0; j < myEnemies[i]->GetBullets().size(); j++)
		{
			Studio::RendererAccessor::GetInstance()->Render(*myEnemies[i]->GetBullets()[j]);
		}

		if (myEnemies[i]->GetPosition().x < 0.0f)
		{
			myEnemies.erase(myEnemies.begin() + i);
		}
	}
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
