#pragma once
#include "Module.h"
#include "rapidjson/document.h"
#include "Counter.h"
#include <vector>
namespace Studio
{
	class Module_Shoot : public Module
	{
	public:
		Module_Shoot(rapidjson::Value& aModuleParameter);

		bool DoStuff(Boss& aBoss) override;
		void ResetModule() override;
	protected:
		

	private:
		VECTOR2F mySpawnPosition;
		VECTOR2F myOriginalSpawnPosition;
		float myElapsedTime;
		float myActiveDuration;
		bool myShootTowardsPlayer;
		bool mySpawnIsRelative;
		std::string myBulletType;
		Counter myCounter;
	};
}

