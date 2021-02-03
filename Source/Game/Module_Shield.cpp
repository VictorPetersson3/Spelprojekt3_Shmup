#include "stdafx.h"
#include "Module_Shield.h"

Studio::Module_Shield::Module_Shield(rapidjson::Value& aModuleParameters) :
	Module_Shield::Module(aModuleParameters)
{
	if (aModuleParameters.HasMember("HitPoints"))
	{
		myHitPoints = aModuleParameters["HitPoints"].GetFloat();
	}
	else
	{
		printf("Duration is not valid in Shield Module\n");
		myHitPoints = 0.5f;
	}
}

bool Studio::Module_Shield::DoStuff(Boss& aBoss)
{
	//TODO Add Shield Object
	printf("Shield not implemented\n");
	return true;
}
