#include "stdafx.h"
#include "Condition_BelowHealth.h"

Studio::Condition_BelowHealth::Condition_BelowHealth(rapidjson::Value& aConditionParameters) :
	Condition_BelowHealth::Condition(aConditionParameters)
{
	myConditionPercentage = aConditionParameters["Percentage"].GetFloat() / 100.0f;
}

bool Studio::Condition_BelowHealth::IsDone(Boss& aBoss)
{
	if (aBoss.GetCurrentHealth() / aBoss.GetMaxHealth() <= myConditionPercentage)
	{
		return true;
	}
	return false;
}
