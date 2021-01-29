#pragma once
#include "Module.h"
#include "rapidjson/document.h"
namespace Studio
{
	class Module_Delay : public Module
	{
	public:
		Module_Delay(rapidjson::Value& aModuleParameters);
		
		bool DoStuff() override;
	private:
		float myDelayTime;
		float myElapsedTime;

	};
}

