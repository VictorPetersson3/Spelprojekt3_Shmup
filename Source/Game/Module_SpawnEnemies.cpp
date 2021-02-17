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
	
	if (aModuleParameters.HasMember("X"))
	{
		float x, y;

		x = aModuleParameters["X"].GetFloat();
		y = aModuleParameters["Y"].GetFloat();

		myOriginalSpawnPosition = { x , y };
	}
}

bool Studio::Module_SpawnEnemies::DoStuff(Boss& aBoss)
{
	if (mySpawnIsRelative)
	{
		mySpawnPosition.x = aBoss.GetPosition()->x - myOriginalSpawnPosition.x;
		mySpawnPosition.y = aBoss.GetPosition()->y - myOriginalSpawnPosition.y;
	}
	else
	{
		mySpawnPosition.x = SCREEN_WIDTH - myOriginalSpawnPosition.x;
		mySpawnPosition.y = myOriginalSpawnPosition.y + SCREEN_HEIGHT * 0.5f;
	}
	auto enemy = Studio::LevelAccessor::GetInstance()->myEnemyFactory->CreateEnemyObject(myType, mySpawnPosition);
	Studio::LevelAccessor::GetInstance()->AddEnemy(enemy);
	return true;
}

void Studio::Module_SpawnEnemies::ResetModule()
{
}
