#include "stdafx.h"
#include "Module_Immunity.h"

Studio::Module_Immunity::Module_Immunity(rapidjson::Value& aModuleParameters) :
	Module(aModuleParameters)
{
	if (aModuleParameters["On"].IsString())
	{
		std::string name = aModuleParameters["On"].GetString();
		if (name == "On")
		{
			myGodmodeChoice = true;
		}
		else if (name == "Off")
		{
			myGodmodeChoice = false;
		}
		else
		{
			printf("Module immunity is not read correctly\n");
		}
	}
	else
	{
		printf("Module immunity is not read correctly\n");
	}
}

bool Studio::Module_Immunity::DoStuff(Boss& aBoss)
{
	aBoss.SetGodMode(myGodmodeChoice);
	return true;
}

void Studio::Module_Immunity::ResetModule()
{
}
