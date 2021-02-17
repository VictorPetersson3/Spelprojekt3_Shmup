#include "stdafx.h"
#include "Module_Shoot.h"
#include "LevelAccessor.h"
#include "PlayerAccessor.h"
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
		//printf("%f\n", aModuleParameter["Interval"].GetFloat() / 1000.0f);
	}
	else
	{
		printf("Interval in Shoot Module is not read correctly\n");
		myCounter.SetInterval(0.1f);
	}
	if (aModuleParameter.HasMember("ShootTowardsPlayer"))
	{
		std::string type = aModuleParameter["ShootTowardsPlayer"].GetString();
		if  (type == "Yes")
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
		myBulletType = "Boss"/*aModuleParameter["Type"].GetString()*/;
	}
	else
	{
		printf("BulletType in Shoot Module is not read correctly\n");
		myBulletType = "Boss";
	}
	if (aModuleParameter.HasMember("Style"))
	{
		std::string style = aModuleParameter["Style"].GetString();
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
		printf("Style in Shoot Module is not read correctly\n");
	}

	if (aModuleParameter.HasMember("X"))
	{
		float x;
		float y;

		x = aModuleParameter["X"].GetFloat();
		y = aModuleParameter["Y"].GetFloat();


		
		myOriginalSpawnPosition = { x , y };

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
		mySpawnPosition.x = aBoss.GetPosition()->x + myOriginalSpawnPosition.x;
		mySpawnPosition.y = aBoss.GetPosition()->y + myOriginalSpawnPosition.y;
	}
	else
	{
		mySpawnPosition.x = SCREEN_WIDTH - myOriginalSpawnPosition.x;
		mySpawnPosition.y = myOriginalSpawnPosition.y + SCREEN_HEIGHT * 0.5f;
	}
	myCounter.Tick();
	myElapsedTime += Studio::Timer::GetInstance()->TGetDeltaTime();
	if (myCounter.PastInterval())
	{
		if (myShootTowardsPlayer)
		{
			VECTOR2F direction = mySpawnPosition - Studio::PlayerAccessor::GetInstance()->GetPosition();
			Studio::LevelAccessor::GetInstance()->SpawnBullet(myBulletType, mySpawnPosition, direction.GetNormalized(), 1);
		}
		else
		{
			Studio::LevelAccessor::GetInstance()->SpawnBullet(myBulletType, mySpawnPosition, 1);
		}
	}
	if (myElapsedTime >= myActiveDuration)
	{
		myElapsedTime = 0.0f;
		return true;
	}
	return false;
}

void Studio::Module_Shoot::ResetModule()
{
}
