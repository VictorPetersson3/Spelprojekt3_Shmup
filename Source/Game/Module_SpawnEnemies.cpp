#include "stdafx.h"
#include "Module_SpawnEnemies.h"
#include "LevelAccessor.h"
#include "EnemyFactory.h"

Studio::Module_SpawnEnemies::Module_SpawnEnemies(rapidjson::Value& aModuleParameters) :
	Module_SpawnEnemies::Module(aModuleParameters)
{
	if (aModuleParameters.HasMember("Type"))
	{
		myType = aModuleParameters["Type"].GetString();
	}
	else
	{
		printf_s("Enemy Type is not being correctly read throug JSON in Boss Module\n");
		myType = "Default";
	}
	if (aModuleParameters.HasMember("Style"))
	{
		std::string style = aModuleParameters["Style"].GetString();
		if (style == "Absolute")
		{
			mySpawnIsRelative = false;
		}
		else
		{
			mySpawnIsRelative = true;
		}
	}
	else
	{
		printf("Parameter Style is not correct in spawn enemies\n");
	}
	
	if (aModuleParameters.HasMember("X"))
	{
		float x, y;

		x = aModuleParameters["X"].GetFloat();
		y = aModuleParameters["Y"].GetFloat();

		x = SCREEN_WIDTH - x;
		y = y + SCREEN_HEIGHT * 0.5f;
		mySpawnPosition = { x , y };
	}
	else
	{
		printf("SpawnPosition of boss enemies is not correct\n");
	}
}

bool Studio::Module_SpawnEnemies::DoStuff(Boss& aBoss)
{
	if (mySpawnIsRelative)
	{
		mySpawnPosition.x = aBoss.GetPosition()->x - mySpawnPosition.x;
		mySpawnPosition.y = aBoss.GetPosition()->y - mySpawnPosition.y;
	}
	auto enemy = Studio::LevelAccessor::GetInstance()->myEnemyFactory->CreateEnemyObject(myType, mySpawnPosition);
	Studio::LevelAccessor::GetInstance()->AddEnemy(enemy);
	//printf("Spawned Enemy Done\n");
	return true;
}
