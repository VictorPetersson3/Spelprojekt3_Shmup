#include "stdafx.h"
#include "Condition_Timed.h"

Studio::Condition_Timed::Condition_Timed(rapidjson::Value& aConditionParameters) :
	Condition_Timed::Condition(aConditionParameters)
{
}

bool Studio::Condition_Timed::IsDone()
{
	return false;
}
