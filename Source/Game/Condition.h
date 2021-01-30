#pragma once
#include "rapidjson/document.h"
namespace Studio
{
	class Condition
	{
	public:
		Condition(rapidjson::Value& aConditionParameters);
		virtual ~Condition();

		virtual bool IsDone() = 0;

	private:


	};

}

