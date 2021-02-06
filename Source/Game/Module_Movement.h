#pragma once
#include "Module.h"

namespace Studio
{
	class Movement;


	class Module_Movement : public Module
	{
	public:
		Module_Movement(rapidjson::Value& aModuleParameters);
		~Module_Movement();

		bool DoStuff(Boss& aBoss) override;
		void ResetModule() override;
	private:
		bool myHasSetStartPos;
		bool myHasChangedPhaseMovement;

		float mySpeed;
		float myHeight;
		float myHorizontalSpeed;
		float myVerticalSpeed;

		VECTOR2F myStartPosition;
		Movement* myModuleMovement;
		Enums::MovementPattern myMovementPattern;
	};

}

