#include "stdafx.h"
#include "Module_Delay.h"
#include "Timer.h"

Studio::Module_Delay::Module_Delay(rapidjson::Value& aModuleParameters) :
	Module_Delay::Module(aModuleParameters)
{
	if (aModuleParameters.HasMember("Seconds"))
	{
		myDelayTime = aModuleParameters["Seconds"].GetFloat();
	}
	else
	{
		printf_s("Module Delay Time is not set correct\n");
		myDelayTime = 0.5f;
	}
	myElapsedTime = 0.0f;
}

bool Studio::Module_Delay::DoStuff(Boss& aBoss)
{
	myElapsedTime += Studio::Timer::GetInstance()->TGetDeltaTime();

	if (myElapsedTime >= myDelayTime)
	{
		printf("Delay Done\n");
		myElapsedTime = 0.0f;
		return true;
	}
	return false;
}
