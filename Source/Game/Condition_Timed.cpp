#include "stdafx.h"
#include "Condition_Timed.h"

Studio::Condition_Timed::Condition_Timed(rapidjson::Value& aConditionParameters) :
	Condition_Timed::Condition(aConditionParameters)
{
	if (aConditionParameters.HasMember("Minutes") && aConditionParameters["Minutes"].IsFloat())
	{
		myCondition = aConditionParameters["Minutes"].GetFloat();
		myCondition *= 60.0f;
	}
}

bool Studio::Condition_Timed::IsDone(Boss& aBoss)
{
	if (aBoss.GetTotalBossTime() >= myCondition)
	{
		return true;
	}
	return false;
}
