#pragma once
#include "Module.h"
#include <vector>
namespace Studio
{
	class Module_Shoot : public Module
	{
	public:
		Module_Shoot();
		~Module_Shoot();

		void DoStuff() override;

	protected:
		

	private:
		std::vector<VECTOR2F*> myBulletSpawnPositions;

	};
}

