#include "stdafx.h"
#include "Module_Shoot.h"
#include "LevelAccessor.h"
#include "Timer.h"

Studio::Module_Shoot::Module_Shoot(rapidjson::Value& aModuleParameter) :
	Module_Shoot::Module(aModuleParameter)
{
	if (aModuleParameter.HasMember("Duration"))
	{
		myActiveDuration = aModuleParameter["Duration"].GetFloat();
	}
	else
	{
		printf("Duration in Shoot Module is not read correctly\n");
		myActiveDuration = 0.0f;
	}
	if (aModuleParameter.HasMember("Interval"))
	{
		myCounter.SetInterval(aModuleParameter["Interval"].GetFloat() / 1000.0f);
		printf("%f\n", aModuleParameter["Interval"].GetFloat() / 1000.0f);
	}
	else
	{
		printf("Interval in Shoot Module is not read correctly\n");
		myCounter.SetInterval(0.1f);
	}
	if (aModuleParameter.HasMember("ShootTowardsPlayer"))
	{
		if (aModuleParameter["ShootTowardsPlayer"].GetString() == "Yes")
		{
			myShootTowardsPlayer = true;
		}
		else
		{
			myShootTowardsPlayer = false;
		}
	}
	else
	{
		printf("ShootTowardsPlayer in Shoot Module is not read correctly\n");
		myShootTowardsPlayer = false;
	}
	if (aModuleParameter.HasMember("Type"))
	{
		myBulletType = "Enemy"/*aModuleParameter["Type"].GetString()*/;
	}
	else
	{
		printf("BulletType in Shoot Module is not read correctly\n");
		myBulletType = "Enemy";
	}
	if (aModuleParameter.HasMember("Style"))
	{
		std::string style = aModuleParameter["Style"].GetString();
		if (style == "Relative")
		{
			mySpawnIsRelative = true;
		}
	}
	else
	{
		printf("Style in Shoot Module is not read correctly\n");
		mySpawnIsRelative = false;
	}

	if (aModuleParameter.HasMember("X"))
	{
		float x;
		float y;

		x = aModuleParameter["X"].GetFloat();
		y = aModuleParameter["Y"].GetFloat();


		
		mySpawnPosition = { x , y };

	}
	else
	{
		printf("Position in Shoot Module is not read correctly\n");
	}

	myElapsedTime = 0.0f;
}

bool Studio::Module_Shoot::DoStuff(Boss& aBoss)
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
	myCounter.Tick();
	myElapsedTime += Studio::Timer::GetInstance()->TGetDeltaTime();
	if (myCounter.PastInterval())
	{
		Studio::LevelAccessor::GetInstance()->SpawnBullet(myBulletType, mySpawnPosition);
		//printf("Spawned Bullet\n");
	}
	if (myElapsedTime >= myActiveDuration)
	{
		myElapsedTime = 0.0f;
		//printf("Shoot Done\n");
		return true;
	}
	return false;
}
