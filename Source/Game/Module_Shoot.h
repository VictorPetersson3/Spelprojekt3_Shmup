#pragma once
#include "Module.h"
#include "rapidjson/document.h"
#include <vector>
namespace Studio
{
	class Module_Shoot : public Module
	{
	public:
		Module_Shoot(rapidjson::Value& aModuleParameter);

		bool DoStuff() override;

	protected:
		

	private:
		std::vector<VECTOR2F*> myBulletSpawnPositions;
		float myShootInterval;
		float myActiveDuration;
		bool myShootTowardsPlayer;
		const char* myBulletType;
	};
}

