#pragma once
#include "Boss.h"
#include "rapidjson/document.h"
namespace Studio
{
	class Condition
	{
	public:
		Condition(rapidjson::Value& aConditionParameters);
		virtual ~Condition();

		virtual bool IsDone(Boss& aBoss) = 0;

	private:


	};

}

