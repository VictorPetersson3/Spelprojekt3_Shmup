#include "stdafx.h"
#include "Module_Missile.h"
#include "LevelAccessor.h"

Studio::Module_Missile::Module_Missile(rapidjson::Value& aModuleParameters) :
	Module(aModuleParameters)
{
	if (aModuleParameters.HasMember("InitialSpeed"))
	{
		myDecceleration = aModuleParameters["Deacceleration"].GetFloat();
		myInitialSpeed = aModuleParameters["InitialSpeed"].GetFloat();
		myAcceleration = aModuleParameters["Acceleration"].GetFloat();

		float x = aModuleParameters["X"].GetFloat();
		float y = aModuleParameters["Y"].GetFloat();

		
		mySpawnPosition = { x, y };

		if (aModuleParameters.HasMember("Style"))
		{
			std::string style = aModuleParameters["Style"].GetString();
			if (style == "Relative")
			{
				myIsRelative = true;
			}
			else
			{
				myIsRelative = false;
			}
		}
	}
}

bool Studio::Module_Missile::DoStuff(Boss& aBoss)
{
	if (myIsRelative)
	{
		mySpawnPosition.x = aBoss.GetPosition()->x - mySpawnPosition.x;
		mySpawnPosition.y = aBoss.GetPosition()->y - mySpawnPosition.y;
	}
	else
	{
		mySpawnPosition.x = SCREEN_WIDTH - mySpawnPosition.x;
		mySpawnPosition.y = mySpawnPosition.y + SCREEN_HEIGHT * 0.5f;
	}

	Studio::LevelAccessor::GetInstance()->SpawnMissile(Enums::BulletOwner::Enemy, mySpawnPosition, -1.0f);

	printf("Missile Launched from boss\n");

	return true;
}
