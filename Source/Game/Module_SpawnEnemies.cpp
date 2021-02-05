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
		if (style == "Relative")
		{
			mySpawnIsRelative = true;
		}
		else
		{
			mySpawnIsRelative = false;
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
	else
	{
		mySpawnPosition.x = SCREEN_WIDTH - mySpawnPosition.x;
		mySpawnPosition.y = mySpawnPosition.y + SCREEN_HEIGHT * 0.5f;
	}
	auto enemy = Studio::LevelAccessor::GetInstance()->myEnemyFactory->CreateEnemyObject(myType, mySpawnPosition);
	Studio::LevelAccessor::GetInstance()->AddEnemy(enemy);
	//printf("Spawned Enemy Done\n");
	return true;
}

void Studio::Module_SpawnEnemies::ResetModule()
{
}
