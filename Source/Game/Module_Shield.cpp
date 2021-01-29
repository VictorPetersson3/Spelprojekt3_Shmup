#include "stdafx.h"
#include "Module_Shield.h"

Studio::Module_Shield::Module_Shield(rapidjson::Value& aModuleParameters) :
	Module_Shield::Module(aModuleParameters)
{
	if (aModuleParameters.HasMember("Duration") && aModuleParameters["Duration"].IsFloat())
	{
		myDuration = aModuleParameters["Duration"].GetFloat();
	}
	else
	{
		printf("Duration is not valid in Shield Module");
	}
}

bool Studio::Module_Shield::DoStuff()
{
	return false;
}
