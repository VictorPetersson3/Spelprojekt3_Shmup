#include "stdafx.h"
#include "Phase.h"
#include "rapidjson/document.h"
//Modules
#include "Module.h"
#include "Module_Immunity.h"
#include "Module_Delay.h"
#include "Module_Shield.h"
#include "Module_Shoot.h"
#include "Module_SpawnEnemies.h"

Studio::Phase::Phase(rapidjson::Value& aPhaseParameters)
{
	if (aPhaseParameters.IsArray())
	{
		auto modules = aPhaseParameters.GetArray();
		for (size_t i = 0; i < modules.Size(); i++)
		{
			if (modules[i]["Module"].GetString() == "Immunity")
			{
				myModules.push_back(new Module_Immunity(modules[i]));
			}
			if (modules[i]["Module"].GetString() == "Delay")
			{
				myModules.push_back(new Module_Delay(modules[i]));
			}
			if (modules[i]["Module"].GetString() == "Enemy")
			{
				myModules.push_back(new Module_SpawnEnemies(modules[i]));
			}
			if (modules[i]["Module"].GetString() == "Ability")
			{
				myModules.push_back(new Module_Shield(modules[i]));
			}
			if (modules[i]["Module"].GetString() == "Shoot")
			{
				myModules.push_back(new Module_Shoot(modules[i]));
			}
		}

		//Read whether the phase is looped or just done once
	}

}

Studio::Phase::~Phase()
{
}
