#pragma once
#include "Module.h"
#include "rapidjson/document.h"
namespace Studio
{
	class Module_Shield : public Module
	{
	public:
		Module_Shield(rapidjson::Value& aModuleParameters);

		bool DoStuff() override;

	protected:

	private:
		VECTOR2F myShieldCenter;
		float myDuration;
	};
}


