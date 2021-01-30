#pragma once
#include "Module.h"
#include "rapidjson/document.h"
namespace Studio
{
	class Module_SpawnEnemies : public Module
	{
	public:
		Module_SpawnEnemies(rapidjson::Value& aModuleParameters);

		bool DoStuff() override;

	private:
		const char* myType;
		VECTOR2F mySpawnPosition;
	};

}

