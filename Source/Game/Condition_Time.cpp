#include "stdafx.h"
#include "Condition_Time.h"
#include "Timer.h"

Studio::Condition_Time::Condition_Time(rapidjson::Value& aConditionParameters) :
	Condition_Time::Condition(aConditionParameters)
{
	if (aConditionParameters.HasMember("Seconds") && aConditionParameters["Seconds"].IsFloat())
	{
		myCondition = aConditionParameters["Seconds"].GetFloat();
	}
	else
	{
		printf("Condition parameter: %f is not read correctly\n", aConditionParameters["Seconds"].GetFloat());
	}
	myElapsedTime = 0.0f;
}

bool Studio::Condition_Time::IsDone(Boss& aBoss)
{
	myElapsedTime += Timer::GetInstance()->TGetDeltaTime();
	if (myElapsedTime >= myCondition)
	{
		return true;
	}
	return false;
}
