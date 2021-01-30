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

		void InitPhase();
		void PlayModules(Boss* aBossObject);


	protected:


		
	private:
		std::vector<Module*> myModules;
		int myModuleAmount;
		int myCurrentModule;
	};
}

