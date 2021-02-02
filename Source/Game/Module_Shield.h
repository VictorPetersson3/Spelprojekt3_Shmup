#pragma once
#include "Module.h"
#include "rapidjson/document.h"
namespace Studio
{
	class Module_Shield : public Module
	{
	public:
		Module_Shield(rapidjson::Value& aModuleParameters);

		bool DoStuff(Boss& aBoss) override;

	protected:

	private:
		VECTOR2F myShieldCenter;
		float myHitPoints;
	};
}


