#pragma once
#include "Module.h"
namespace Studio
{
	class Module_Laser : public Module
	{
	public:
		Module_Laser(rapidjson::Value& aModuleParameters);

		bool DoStuff(Boss& aBoss) override;
		void ResetModule() override;

	private:
		float myDuration;
		float myElapsedTime;
	};
}

