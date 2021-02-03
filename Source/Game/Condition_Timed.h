#pragma once
#include "Condition.h"
#include "rapidjson/document.h"
namespace Studio
{
	class Condition_Timed : public Condition
	{
	public:
		Condition_Timed(rapidjson::Value& aConditionParameters);

		bool IsDone(Boss& aBoss) override;

	private:

		float myCondition;
	};

}

