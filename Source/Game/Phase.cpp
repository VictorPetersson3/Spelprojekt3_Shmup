#include "stdafx.h"
#include "Phase.h"
#include "rapidjson/document.h"
//Modules
#include "Module.h"
#include "Module_Immunity.h"
#include "Module_Delay.h"
#include "Module_Shield.h"
#include "Module_Missile.h"
#include "Module_Shoot.h"
#include "Module_SpawnEnemies.h"
#include "Module_Movement.h"
#include "Module_Laser.h"

//Gameplay
#include "Boss.h"

Studio::Phase::Phase(rapidjson::Value& aPhaseParameters)
{
	if (aPhaseParameters.IsArray())
	{
		auto modules = aPhaseParameters.GetArray();
		for (size_t i = 0; i < modules.Size(); i++)
		{
			if (modules[i].HasMember("Module") && modules[i]["Module"].IsString())
			{
				std::string type = modules[i]["Module"].GetString();
				if (type == "Immunity")
				{
					myModules.push_back(new Module_Immunity(modules[i]));
				}
				else if (type == "Delay")
				{
					myModules.push_back(new Module_Delay(modules[i]));
				}
				else if (type == "Enemy")
				{
					myModules.push_back(new Module_SpawnEnemies(modules[i]));
				}
				else if (type == "Ability")
				{

					if (modules[i].HasMember("Ability") && modules[i]["Ability"].IsString())
					{
						std::string ability = modules[i]["Ability"].GetString();
						if (ability == "Shield")
						{
							myModules.push_back(new Module_Shield(modules[i]));
						}
						if (ability == "Missile")
						{
							myModules.push_back(new Module_Missile(modules[i]));
						}
					}
				}
				else if (type == "Shoot")
				{
					myModules.push_back(new Module_Shoot(modules[i]));
				}
				else if (type == "Movement")
				{
					myModules.push_back(new Module_Movement(modules[i]));

				}
				else if (type == "Laser")
				{
					myModules.push_back(new Module_Laser(modules[i]));

				}
			}
		}
	}
	myModuleAmount = static_cast<int>(myModules.size());
	myCurrentModule = 0;
	myHasPlayedOnce = false;
}

Studio::Phase::~Phase()
{
	for (Module* module : myModules)
	{
		SAFE_DELETE(module);
	}
	myModules.clear();
}

bool Studio::Phase::HavePlayedOnce()
{
	return myHasPlayedOnce;
}

void Studio::Phase::PlayModules(Boss* aBossObject)
{
	//TODO
	// - Change Name For Module Function
	if (!myModules.empty())
	{
		if (myModules[myCurrentModule]->DoStuff(*aBossObject))
		{
			if (myCurrentModule < myModuleAmount - 1)
			{
				myCurrentModule++;
			}
			else
			{
				myHasPlayedOnce = true;
				myCurrentModule = 0;
			}
		}
	}

}

void Studio::Phase::ResetPhase()
{
	for (Module* module : myModules)
	{
		module->ResetModule();
	}

	myHasPlayedOnce = false;
	myCurrentModule = 0;
}
