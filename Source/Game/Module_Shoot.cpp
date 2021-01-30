#include "stdafx.h"
#include "Module_Shoot.h"
#include "LevelAccessor.h"
#include "Timer.h"

Studio::Module_Shoot::Module_Shoot(rapidjson::Value& aModuleParameter) :
	Module_Shoot::Module(aModuleParameter)
{
	if (aModuleParameter.HasMember("Duration") && aModuleParameter["Duration"].IsFloat())
	{
		myActiveDuration = aModuleParameter["Duration"].GetFloat();
	}
	else
	{
		myActiveDuration = 0.0f;
	}
	if (aModuleParameter.HasMember("Interval") && aModuleParameter["Interval"].IsFloat())
	{
		myCounter.SetInterval(aModuleParameter["Interval"].GetFloat());
	}
	else
	{
		myCounter.SetInterval(0.1f);
	}
	if (aModuleParameter.HasMember("ShootTowardsPlayer") && aModuleParameter["ShootTowardsPlayer"].IsString())
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
		myShootTowardsPlayer = false;
	}
	if (aModuleParameter.HasMember("Type") && aModuleParameter["Type"].IsString())
	{
		myBulletType = aModuleParameter["Type"].GetString();
	}
	else
	{
		myBulletType = "Enemy";
	}
	myElapsedTime = 0.0f;
}

bool Studio::Module_Shoot::DoStuff()
{
	myCounter.Tick();
	myElapsedTime += Studio::Timer::GetInstance()->TGetDeltaTime();
	if (myCounter.PastInterval())
	{
		for (VECTOR2F* position : myBulletSpawnPositions)
		{
			Studio::LevelAccessor::GetInstance()->SpawnBullet(myBulletType, *position);
		}
	}
	if (myElapsedTime >= myActiveDuration)
	{
		myElapsedTime = 0.0f;
		return true;
	}
	return false;
}
