#include "stdafx.h"
#include "Condition_Time.h"

Studio::Condition_Time::Condition_Time(rapidjson::Value& aConditionParameters) :
	Condition_Time::Condition(aConditionParameters)
{
}

bool Studio::Condition_Time::IsDone()
{
	return false;
}
