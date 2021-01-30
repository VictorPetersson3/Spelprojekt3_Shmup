#include "stdafx.h"
#include "Condition_BelowHealth.h"

Studio::Condition_BelowHealth::Condition_BelowHealth(rapidjson::Value& aConditionParameters) :
	Condition_BelowHealth::Condition(aConditionParameters)
{
}

bool Studio::Condition_BelowHealth::IsDone()
{
	return false;
}
