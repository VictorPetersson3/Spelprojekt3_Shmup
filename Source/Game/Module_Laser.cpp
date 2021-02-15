#include "stdafx.h"
#include "Module_Laser.h"
#include "LevelAccessor.h"
#include "Timer.h"

Studio::Module_Laser::Module_Laser(rapidjson::Value& aModuleParameters) :
	Module(aModuleParameters)
{
	if (aModuleParameters.HasMember("Duration"))
	{
		myDuration = aModuleParameters["Duration"].GetFloat();
	}
	else
	{
		printf_s("Module Laser duration is not set correct\n");
		myDuration = 0.5f;
	}
	myElapsedTime = 0.0f;
}

bool Studio::Module_Laser::DoStuff(Boss& aBoss)
{
	myElapsedTime += Studio::Timer::GetInstance()->TGetDeltaTime();

	if (myElapsedTime >= myDuration)
	{
		myElapsedTime = 0.0f;
		Studio::LevelAccessor::GetInstance()->FireLaser(false);
		return true;
	}
	Studio::LevelAccessor::GetInstance()->FireLaser(true);
	return false;
}

void Studio::Module_Laser::ResetModule()
{
	myElapsedTime = 0.0f;
	Studio::LevelAccessor::GetInstance()->FireLaser(false);
}
