#pragma once
#include "Module.h";
namespace Studio
{
	class Module_Missile : public Module
	{
	public:
		Module_Missile(rapidjson::Value& aModuleParameters);

		bool DoStuff(Boss& aBoss) override;

	private:

		float myInitialSpeed;
		float myDecceleration;
		float myAcceleration;

		bool myIsRelative;

		VECTOR2F mySpawnPosition;
	};
}


