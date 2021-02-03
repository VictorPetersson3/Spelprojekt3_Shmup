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

	private:
		bool myHasSetStartPos;
		VECTOR2F myStartPosition;
		Movement* myModuleMovement;
	};

}

