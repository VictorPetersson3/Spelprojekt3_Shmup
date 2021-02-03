#pragma once
#include "Condition.h"
#include "rapidjson/document.h"

namespace Studio
{
	class Condition_Time : public Condition
	{
	public:
		Condition_Time(rapidjson::Value& aConditionParameters);

		bool IsDone(Boss& aBoss) override;


	private:
		float myCondition;
		float myElapsedTime;
	};

}

