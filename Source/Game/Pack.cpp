#include "stdafx.h"
#include "Pack.h"
#include "LevelManager.h"

#include <tga2d/sprite/sprite.h>

#include "EnemyFactory.h"

#include "Counter.h"

namespace Studio
{
	Pack::Pack(LevelManager* aLevelManager, rapidjson::Value& anEnemyArray) : myLevelManager(aLevelManager)
	{
		myExitConditionHasBeenMet = false;
		SAFE_CREATE(myCounter, Counter());

		int c = 0;
		if (anEnemyArray.HasMember("Enemies") && anEnemyArray["Enemies"].IsArray())
		{
			auto enemies = anEnemyArray["Enemies"].GetArray();
			for (size_t i = 0; i < enemies.Size(); i++)
			{
				float x, y;

				x = enemies[i]["Position"]["X"].GetFloat();
				y = enemies[i]["Position"]["Y"].GetFloat();

				x = SCREEN_WIDTH - x;
				y = y + SCREEN_HEIGHT * 0.5f;
				printf_s("Stored enemy at location {x: %f, y: %f}\n", x, y);

				// Store the interval at when the enemy should be spawned
				myTimedIntervals.push_back(enemies[i]["Timer"].GetFloat() / 1000.0f);

				// Create enemy and store it
				auto enemy = myLevelManager->myEnemyFactory->CreateEnemyObject(enemies[i]["Type"].GetString(), { x, y });
				myStoredEnemies.push_back(enemy);
				c++;
			}

			if (enemies.Size() > 0)
			{
				myCounter->SetInterval(myTimedIntervals[0]);
			}
		}
		else
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_RED);
			printf_s("ERROR: Corrupted pack found in \"%s\", missing Enemies\n", myLevelManager->CurrentLevelPath());
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
		}

		printf_s("This pack had %i enemies in it\n", c);
	}
	
	Pack::~Pack()
	{
		SAFE_DELETE(myCounter);
		SAFE_DELETE_VECTOR(myStoredEnemies);
	}

	bool Pack::ExitConditionIsMet()
	{
		return myExitConditionHasBeenMet;
	}

	void Pack::TransferTopEnemyToLevelManager()
	{
		if (myStoredEnemies.size() > 0)
		{
			myCounter->Tick();
			if (myCounter->PastInterval())
			{
				printf_s("Transfered an enemy\n");
				myLevelManager->AddEnemy(myStoredEnemies[0]);
				myTransferredEnemies.push_back(myStoredEnemies[0]); // Future proofing for ExitCondition
				myStoredEnemies.erase(myStoredEnemies.begin());
				printf_s("Enemies left in storage: %i\n", myStoredEnemies.size());

				myTimedIntervals.erase(myTimedIntervals.begin());
				if (myTimedIntervals.size() > 0)
				{
					myCounter->SetInterval(myTimedIntervals[0]);
				}
			}
		}
	}

	void Pack::CheckIfExitConditionHasBeenMet()
	{
		myExitConditionHasBeenMet = (myStoredEnemies.size() == 0);

		/*bool allTransferredEnemiesAreDead = true;
		for (int i = myTransferredEnemies.size() - 1; i >= 0; i--)
		{
			if (myTransferredEnemies[i])
			{
				allTransferredEnemiesAreDead = false;
				break;
			}
			else
			{
				myTransferredEnemies.erase(myTransferredEnemies.begin() + i);
			}
		}

		myExitConditionHasBeenMet = allTransferredEnemiesAreDead;*/
	}

	void Pack::Update()
	{
		TransferTopEnemyToLevelManager();
		CheckIfExitConditionHasBeenMet();
	}
}
