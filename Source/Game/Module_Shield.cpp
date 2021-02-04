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
	myHasCreatedShield = false;
}

bool Studio::Module_Shield::DoStuff(Boss& aBoss)
{
	if (!myHasCreatedShield)
	{
		aBoss.ActivateShield(new Shield(myHitPoints));
		myHasCreatedShield = true;
		printf("Shield Activated\n");
	}
	return true;
}
