#include "stdafx.h"
#include "LevelManager.h"
#include "rapidjson/document.h"

// Filhantering
#include <fstream>
#include <sstream>
#include <filesystem>

// Spelfiler
#include "Timer.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Pack.h"
#include "EnemyFactory.h"
#include "BulletFactory.h"
#include "Player.h"
#include "Boss.h"
#include "BossManager.h"

// Rendering
#include "RendererAccessor.h"
#include "Renderer.h"
#include <tga2d/sprite/sprite.h>

// Menu
#include "MenuManagerSingleton.h"
#include "MenuManager.h"
#include "MenuObject.h"

// Input
#include "InputManager.h"

namespace Studio
{
	LevelManager::LevelManager()
	{
		SAFE_CREATE(myEnemyFactory, EnemyFactory());
		SAFE_CREATE(myBulletFactory, BulletFactory());
		myEnemyFactory->InitEnemyType("Sprites/assets/enemies/enemyShip1/enemyShip1.dds", 999, "Default");
		//															    ^ key

		SAFE_CREATE(myBossManager, BossManager());

		//temp BulletFactory to try and spawn bullets via LevelManager -->Pu
		myBulletFactory->InitBulletType("sprites/debugpixel.dds", 12, "Enemy", -500.0f, Enums::BulletOwner::Enemy);
		myBulletFactory->InitBulletType("sprites/debugpixel.dds", 12, "Player", 800.0f, Enums::BulletOwner::Player);
		myBossManager->LoadBosses();
		// Load chosen level by Lever Designers

		

		std::fstream file;
		std::string levelPath;
		file.open("JSON/Levels/level.txt");
		{
			bool lineIsComment = true;
			// Loop through file until line is not a comment
			do
			{
				std::getline(file, levelPath);
				lineIsComment = (levelPath[0] == '#');
			} while (lineIsComment);
		}
		file.close();
		std::string path = "JSON/Levels/";
		path.append(levelPath);
		path.append(".json");

		//printf_s("PATH %s\n", path.c_str());

		LoadLevel(path.c_str());
		std::string directory = "JSON/Levels";
		for (const auto& entry : std::filesystem::directory_iterator(directory))
		{
			if (entry.path().extension().string() == ".json")
			{
				auto file = entry.path().string();
				myLevelPaths.push_back(file);
				printf("LevelPath: %s\n", file.c_str());
			}
		}
	}

	LevelManager::~LevelManager()
	{
		myEnemyFactory->~EnemyFactory();
		SAFE_DELETE(myEnemyFactory);
		SAFE_DELETE_VECTOR(myPacks);
		SAFE_DELETE_VECTOR(myEnemies);
		SAFE_DELETE_VECTOR(myBullets);
		SAFE_DELETE(myBulletFactory);
		SAFE_DELETE(myBossManager);
	}

	void LevelManager::Update(Player* aPlayer)
	{

		if (Studio::InputManager::GetInstance()->IsKeyDown('Y'))
		{
			MenuManagerSingleton::GetInstance()->GetShop()->Enable();
			MenuManagerSingleton::GetInstance()->GetHUD()->Disable();
		}

		if (Studio::InputManager::GetInstance()->IsKeyDown('I'))
		{
			MenuManagerSingleton::GetInstance()->GetShop()->Disable();
			MenuManagerSingleton::GetInstance()->GetHUD()->Enable();
		}

		//Pu som kommer drömma mardrömmar av denna rad
		myPlayer = aPlayer;
		if (myLevelIsCleared == true)
		{

			/*SETCONSOLECOLOR(CONSOLE_COLOR_YELLOW);
			printf_s("Warning: Level is cleared but LevelManager.Update() is still being called.\n");
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);*/
			//myBoss->Update();

			MenuManagerSingleton::GetInstance()->GetShop()->Enable();
			MenuManagerSingleton::GetInstance()->GetHUD()->Disable();

			LevelLogic();
		}
		else
		{
			// Pack
			if (!myCurrentPack->ExitConditionIsMet())
			{
				myCurrentPack->Update();
			}
			else
			{
				if (myPackIndex < myPacks.size() - 1)
				{
					printf_s("changing to next pack from pack %i ...\n", myPackIndex + 1);
					myCurrentPack = myPacks[++myPackIndex];
					printf_s("Size of new pack: %i\n", myCurrentPack->myStoredEnemies.size());
				}
			}
			//Pu
			LevelLogic();
			// Check if Player cleared the level
			CheckIfLevelIsCleared();
		}
	}

	const std::string& LevelManager::CurrentLevelPath()
	{
		return myCurrentLevelPath;
	}

	void LevelManager::AddEnemy(Enemy* anEnemy)
	{
		printf_s("Recieved an enemy\n");
		myEnemies.push_back(anEnemy);
	}

	void LevelManager::SpawnBullet(const std::string& aType, VECTOR2F aPosition)
	{
		Bullet* bullet = myBulletFactory->CreateBulletObject(aType, aPosition);
		if (myPlayer->HasPenetratingRounds() && bullet->GetOwner() == Enums::BulletOwner::Player)
		{
			bullet->SetIsPenetrating();
		}
		myBullets.push_back(bullet);
	}

	bool LevelManager::LevelIsCleared()
	{
		return myLevelIsCleared;
	}

	//Pu
	void LevelManager::LevelLogic()
	{

		// Copy & Paste from Jimmi
		for (size_t i = 0; i < myEnemies.size(); i++)
		{

			myEnemies[i]->Update(Timer::GetInstance()->TGetDeltaTime());
			if (myEnemies[i]->GetCollider().Intersects(myPlayer->GetCollider()) && !myPlayer->GetHasCollided() && myEnemies[i]->GetIsTerrain())
			{
				myPlayer->Bounce(myEnemies[i]->GetPosition());
			}

			if (!myEnemies[i]->IsDead())
			{
				Studio::RendererAccessor::GetInstance()->Render(*myEnemies[i]);
			}

			if (myEnemies[i]->GetPosition().x < 0.0f)
			{
				myEnemies.erase(myEnemies.begin() + i);
			}
		}
		for (Bullet* bullet : myBullets)
		{
			bullet->Update();

			Studio::RendererAccessor::GetInstance()->Render(*bullet);
		}

		for (int i = myBullets.size() - 1; i >= 0; i--)
		{
			if (myBullets[i]->GetPosition().x > 1920 || myBullets[i]->GetPosition().x < 0 || myBullets[i]->GetPosition().y < 0 || myBullets[i]->GetPosition().y > 1080)
			{
				myBullets.erase(myBullets.begin() + i);
			}
		}

		//Pu
		CheckCollision();

		for (int i = myEnemies.size() - 1; i >= 0; i--)
		{
			if (myEnemies[i]->IsDead())
			{
				myEnemies[i]->DeathLogic();
				myEnemies.erase(myEnemies.begin() + i);
			}
		}
		if (myPlayer->IsDead())
		{
			//Reload Level after death explosion is finished
			//LoadLevel(myCurrentLevelPath); 
		}
	}
	//Pu
	void LevelManager::CheckCollision()
	{
		if (myLevelIsCleared)
		{
			for (int i = myBullets.size() - 1; i >= 0; i--)
			{
				if (myBullets[i]->GetOwner() == Studio::Enums::BulletOwner::Player)
				{
					if (!myBoss->IsDead() && myBullets[i]->GetOwner() == Studio::Enums::BulletOwner::Player)
					{
						if (myBoss->Intersects(*myBullets[i]))
						{
							if (myBullets[i]->IsEnemyAlreadyHit(myBoss) == false)
							{
								if (myBullets[i]->GetIsPenetrating() == false)
								{
									myBullets.erase(myBullets.begin() + i);
								}
								myBullets[i]->RegisterEnemyHit(myBoss);
								myBoss->TakeDamage(25.0f);

							}
						}
					}
					//When the boss dies?
					else
					{
						myBoss->TakeDamage(1.0f);
						myBullets.erase(myBullets.begin() + i);
					}
				}
			}
		}
		if (!myBullets.empty())
		{
			for (int j = myBullets.size() - 1; j >= 0; j--)
			{
				if (myBullets[j]->GetOwner() == Studio::Enums::BulletOwner::Enemy)
				{
					if (myPlayer->Intersects(*myBullets[j]))
					{
						myPlayer->TakeDamage(1.0f);
						//printf_s("Current Health: %f\n", myPlayer->GetCurrentHealth());

						myBullets.erase(myBullets.begin() + j);
					}
				}
			}
		}

		if (myEnemies.size() > 0)
		{
			if (myBullets.size() > 0)
			{
				for (int i = myEnemies.size() - 1; i >= 0; i--)
				{
					if (!myEnemies[i]->IsDead())
					{
						for (int j = myBullets.size() - 1; j >= 0; j--)
						{
							if (myBullets[j]->GetOwner() == Studio::Enums::BulletOwner::Player)
							{
								if (myEnemies[i]->Intersects(*myBullets[j]))
								{
									if (myBullets[j]->IsEnemyAlreadyHit(myEnemies[i]) == false)
									{

										myBullets[j]->RegisterEnemyHit(myEnemies[i]);
										myEnemies[i]->TakeDamage(100);

										if (myBullets[j]->GetIsPenetrating() == false)
										{
											myBullets.erase(myBullets.begin() + j);
										}
										
									}
								}
							}
						}
					}
				}
			}
		}
	}

	void LevelManager::LoadLevel(const std::string& aLevelPath)
	{

		myCurrentLevelPath = aLevelPath;
		myLevelIsCleared = false;

		rapidjson::Document document;

		std::string text;
		std::fstream file;
		file.open(aLevelPath);
		{
			std::string line;
			while (std::getline(file, line))
			{
				text.append(line);
			}
		}
		file.close();
		document.Parse(text.c_str());

		if (document.HasMember("Packs"))
		{
			auto packs = document["Packs"].GetArray();

			printf_s("===JSON===\n%s\n==========\n", text.c_str());

			for (rapidjson::SizeType i = 0; i < packs.Size(); i++)
			{
				myPacks.push_back(new Pack(this, packs[i]));
			}

			myPackIndex = 0;
			myCurrentPack = myPacks[myPackIndex];
		}
		else
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_RED);
			printf_s("ERROR: \"%s\" is missing packs\n", myCurrentLevelPath);
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
		}
	}
	const std::string& LevelManager::GetCurrentLevelPath() const
	{
		return myCurrentLevelPath;
	}
	void LevelManager::CheckIfLevelIsCleared()
	{
		// This is NOT how to check if a level has been cleared.
		// TODO: Fix this in beta (maybe check if packs is past mypacks size??)

		if (myPackIndex == myPacks.size() - 1 && myEnemies.size() == 0)
		{
			if (!myLevelIsCleared)
			{
				myBoss = myBossManager->GetLevelBoss(0);
			}
			myLevelIsCleared = true;
		}
	}
}
