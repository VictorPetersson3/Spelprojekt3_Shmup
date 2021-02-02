#include "stdafx.h"
#include "Condition_DoOnce.h"

Studio::Condition_DoOnce::Condition_DoOnce(rapidjson::Value& aConditionParameters) :
	Condition(aConditionParameters)
{
}

bool Studio::Condition_DoOnce::IsDone(Boss& aBoss)
{
	return aBoss.GetCurrentPhaseHasPlayedOnce();
}
