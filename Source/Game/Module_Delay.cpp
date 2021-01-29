#include "stdafx.h"
#include "Module_Delay.h"
#include "Timer.h"

Studio::Module_Delay::Module_Delay(rapidjson::Value& aModuleParameters) :
	Module_Delay::Module(aModuleParameters)
{
	if (aModuleParameters.HasMember("Seconds") && aModuleParameters["Seconds"].IsFloat())
	{
		myDelayTime = aModuleParameters["Seconds"].GetFloat();
	}
	else
	{
		printf_s("Module Delay Time is not set correct");
		myDelayTime = 0.5f;
	}
	myElapsedTime = 0.0f;
}

bool Studio::Module_Delay::DoStuff()
{
	myElapsedTime += Studio::Timer::GetInstance()->TGetDeltaTime();
	if (myElapsedTime >= myDelayTime)
	{
		myElapsedTime = 0.0f;
		return true;
	}
	return false;
}
