#pragma once
#include "Condition.h"
namespace Studio
{
	class Condition_DoOnce : public Condition
	{
	public:
		Condition_DoOnce(rapidjson::Value& aConditionParameters);

		bool IsDone(Boss& aBoss) override;
	private:

	};

}