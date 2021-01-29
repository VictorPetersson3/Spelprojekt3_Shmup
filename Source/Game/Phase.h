#pragma once
#include "rapidjson/document.h"
#include <vector>
namespace Studio
{
	class Module;


	class Phase
	{
	public:
		Phase(rapidjson::Value& aPhaseParameters);
		~Phase();

		void InitPhase();
		void PlayModules();


	protected:


		
	private:
		std::vector<Module*> myModules;

	};
}

