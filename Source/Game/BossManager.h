#pragma once
#include <vector>
namespace Studio
{
	//Forward Declared Classes
	class Boss;

	class BossManager
	{
	public:
		BossManager();
		~BossManager();

		void LoadBosses();

		Boss* GetLevelBoss(int aLevelCount);


	private:
		std::vector<Boss*> myBosses;
		int myCurrentBoss;
		int myAmountOfBosses;
	};
}


