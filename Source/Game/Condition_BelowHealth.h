#pragma once
#include "Condition.h"
#include "rapidjson/document.h"
namespace Studio
{
	class Condition_BelowHealth : public Condition
	{
	public:
		Condition_BelowHealth(rapidjson::Value& aConditionParameters);

		bool IsDone(Boss& aBoss) override;

	private:

		float myConditionPercentage;
	};

}

