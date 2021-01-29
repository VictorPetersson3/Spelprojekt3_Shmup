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
	myElapsedTime = 0.0f;
}

bool Studio::Module_Delay::DoStuff()
{
	myElapsedTime += Studio::Timer::GetInstance()->TGetDeltaTime();
	return (myElapsedTime >= myDelayTime);
}
