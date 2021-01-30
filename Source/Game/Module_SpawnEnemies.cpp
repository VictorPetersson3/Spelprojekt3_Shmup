#include "stdafx.h"
#include "Module_SpawnEnemies.h"
#include "LevelAccessor.h"
#include "EnemyFactory.h"

Studio::Module_SpawnEnemies::Module_SpawnEnemies(rapidjson::Value& aModuleParameters) :
	Module_SpawnEnemies::Module(aModuleParameters)
{
	//Fråga om det här är ett objekt!!!!
	if (aModuleParameters.IsObject())
	{
		if (aModuleParameters.HasMember("Type") && aModuleParameters["Type"].IsString())
		{
			myType = aModuleParameters["Type"].GetString();
		}
		else
		{
			printf_s("Enemy Type is not being correctly read throug JSON in Boss Module");
			myType = nullptr;
		}
		float x, y;

		x = aModuleParameters["X"].GetFloat();
		y = aModuleParameters["Y"].GetFloat();

		x = SCREEN_WIDTH - x;
		y = y + SCREEN_HEIGHT * 0.5f;
		mySpawnPosition = { x , y };
	}
	else
	{
		myType = nullptr;
	}
}

bool Studio::Module_SpawnEnemies::DoStuff()
{
	auto enemy = Studio::LevelAccessor::GetInstance()->myEnemyFactory->CreateEnemyObject(myType, mySpawnPosition);
	Studio::LevelAccessor::GetInstance()->AddEnemy(enemy);
	return true;
}
