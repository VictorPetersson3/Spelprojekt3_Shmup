#include "stdafx.h"
#include "Module_Immunity.h"

Studio::Module_Immunity::Module_Immunity(rapidjson::Value& aModuleParameters) :
	Module(aModuleParameters)
{
	if (aModuleParameters.HasMember("On") && aModuleParameters["On"].IsString())
	{
		if (aModuleParameters["On"].GetString() == "On")
		{
			myGodmodeChoice = true;
		}
		else
		{
			myGodmodeChoice = false;
		}
	}
}

bool Studio::Module_Immunity::DoStuff()
{
	//Set Boss GodMode here TODO also change in health so you can send in a parameter for what you want.
	return true;
}
