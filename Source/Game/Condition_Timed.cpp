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
	else
	{
		printf_s("Enrage Timer Minutes are not read correctly in Boss Conditions\n");
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
