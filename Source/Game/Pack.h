#pragma once
#include <vector>
#include "rapidjson/document.h"
namespace Studio
{
	class Enemy;
	class LevelManager;
	class Counter;
	class Pack
	{
	public:

		Pack(LevelManager*, rapidjson::Value& anEnemyArray);
		~Pack();
		void Update();

		bool ExitConditionIsMet();
		void TransferTopEnemyToLevelManager();

	private:

		void CheckIfExitConditionHasBeenMet();

		std::vector<Enemy*> myStoredEnemies;
		std::vector<Enemy*> myTransferredEnemies;
		std::vector<float> myTimedIntervals;
		LevelManager* myLevelManager;
		bool myExitConditionHasBeenMet;
		Counter* myCounter;
	};
}
