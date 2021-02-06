#pragma once
#include "rapidjson/document.h"
#include <vector>

namespace Studio
{
	class Module;
	class Boss;

	class Phase
	{
	public:
		Phase(rapidjson::Value& aPhaseParameters);
		~Phase();
		bool HavePlayedOnce();
		void PlayModules(Boss* aBossObject);
		void ResetPhase();
	protected:
		
	private:
		std::vector<Module*> myModules;
		Module* myMovementModule;
		int myModuleAmount;
		int myCurrentModule;
		bool myHasPlayedOnce;
		bool myHasMovement;
	};
}

