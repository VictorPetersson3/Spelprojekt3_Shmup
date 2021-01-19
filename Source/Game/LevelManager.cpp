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
		LoadLevel("JSON/Levels/level_x.json");
	}

	LevelManager::~LevelManager()
	{
		myEnemyFactory->~EnemyFactory();
		SAFE_DELETE(myEnemyFactory);
		SAFE_DELETE_VECTOR(myPacks);
		SAFE_DELETE_VECTOR(myEnemies);
		SAFE_DELETE_VECTOR(myBullets);
	}

	void LevelManager::Update()
	{
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

			// Copy & Paste from Jimmi
			for (size_t i = 0; i < myEnemies.size(); i++)
			{
				myEnemies[i]->Update(Timer::GetInstance()->TGetDeltaTime());
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
