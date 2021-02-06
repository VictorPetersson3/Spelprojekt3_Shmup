#pragma once
#include "Module.h"
#include "rapidjson/document.h"
namespace Studio
{
	class Module_Immunity : public Module
	{
	public:
		Module_Immunity(rapidjson::Value& aModuleParameters);

		bool DoStuff(Boss& aBoss) override;
		void ResetModule() override;
	protected:


	private:
		bool myGodmodeChoice;
	};
}

