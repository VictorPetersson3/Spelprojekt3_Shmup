#include "stdafx.h"
#include "LevelManager.h"
#include "rapidjson/document.h"

// Filhantering
#include <fstream>
#include <sstream>

// Spelfiler
#include "Timer.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Pack.h"
#include "EnemyFactory.h"
#include "Player.h"

// Rendering
#include "RendererAccessor.h"
#include "Renderer.h"
#include <tga2d/sprite/sprite.h>

namespace Studio
{
	LevelManager::LevelManager()
	{
		SAFE_CREATE(myEnemyFactory, EnemyFactory());

		myEnemyFactory->InitEnemyType("Sprites/debugpixel.dds", 999, "Default");
		//															    ^ key

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

		printf_s("PATH %s\n", path.c_str());

		LoadLevel(path.c_str());
	}

	LevelManager::~LevelManager()
	{
		myEnemyFactory->~EnemyFactory();
		SAFE_DELETE(myEnemyFactory);
		SAFE_DELETE_VECTOR(myPacks);
		SAFE_DELETE_VECTOR(myEnemies);
		SAFE_DELETE_VECTOR(myBullets);
	}

	void LevelManager::Update(Player* aPlayer)
	{
		//Pu som kommer drömma mardrömmar av denna rad
		myPlayer = aPlayer;
		if (myLevelIsCleared)
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_YELLOW);
			printf_s("Warning: Level is cleared but LevelManager.Update() is still being called.\n");
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
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

	const char* LevelManager::CurrentLevelPath()
	{
		return myCurrentLevelPath;
	}

	void LevelManager::AddEnemy(Enemy* anEnemy)
	{
		printf_s("Recieved an enemy\n");
		myEnemies.push_back(anEnemy);
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
			Studio::RendererAccessor::GetInstance()->Render(*bullet);
		}
		//Pu
		CheckCollision();

		for (int i = myEnemies.size() - 1; i >= 0; i--)
		{
			if (myEnemies[i]->HasFinishedExplosion() && myEnemies[i]->IsDead())
			{
				myEnemies.erase(myEnemies.begin() + i);
			}
		}
		if (myPlayer->IsFinishedExploding() && myPlayer->IsDead())
		{
			//Reload Level after death explosion is finished
			//LoadLevel(myCurrentLevelPath); 
		}
	}
	//Pu
	void LevelManager::CheckCollision()
	{
		bool shouldExplode = false;
		if (myEnemies.size() > 0)
		{
			for (int i = 0; i < myEnemies.size(); i++)
			{
				if (myEnemies[i]->GetBullets().size() > 0)
				{
					for (int j = myEnemies[i]->GetBullets().size() - 1; j >= 0; j--)
					{
						if (myPlayer->Intersects(*myEnemies[i]->GetBullets()[j]))
						{
							myPlayer->TakeDamage(25);
							printf_s("Current Health: %f\n", myPlayer->GetCurrentHealth());
							if (myPlayer->IsDead())
							{
								myPlayer->PlayExplosion();
							}
							myEnemies[i]->GetBullets().erase(myEnemies[i]->GetBullets().begin() + j);
						}
					}
				}
			}

			if (myPlayer->GetBullets().size() > 0)
			{
				for (int i = myEnemies.size() - 1; i >= 0; i--)
				{
					if (!myEnemies[i]->IsDead())
					{
						for (int j = myPlayer->GetBullets().size() - 1; j >= 0; j--)
						{
							if (myPlayer->GetBullets()[j]->Intersects(*myEnemies[i]))
							{
								myPlayer->GetBullets().erase(myPlayer->GetBullets().begin() + j);
								myEnemies[i]->TakeDamage(100);
								if (myEnemies[i]->IsDead())
								{
									shouldExplode = true;
								}
							}
						}
					}
					if (shouldExplode)
					{
						myEnemies[i]->PlayExplosion();
						shouldExplode = false;
					}
				}
			}
		}
	}

	void LevelManager::LoadLevel(const char* aLevelPath)
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
	const char* LevelManager::GetCurrentLevelPath() const
	{
		return myCurrentLevelPath;
	}
	void LevelManager::CheckIfLevelIsCleared()
	{
		// This is NOT how to check if a level has been cleared.
		// TODO: Fix this in beta (maybe check if packs is past mypacks size??)

		if (myPackIndex == myPacks.size() - 1 && myEnemies.size() == 0)
		{
			myLevelIsCleared = true;
		}
	}
}
