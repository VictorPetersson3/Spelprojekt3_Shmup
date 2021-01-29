#pragma once
#include "Module.h"
#include <vector>
namespace Studio
{
	class Phase
	{
	public:
		Phase();
		~Phase();

		void InitPhase();


	protected:


		
	private:
		std::vector<Module*> myModules;

	};
}

