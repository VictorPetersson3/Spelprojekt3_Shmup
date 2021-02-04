#pragma once
#include "GameObject.h"
#include "Enums.h"
#include "HealthBar.h"
#include "rapidjson/document.h"
#include <vector>
namespace Studio
{
	//Forward Declaring Classes
	class RenderCommand;
	class Bullet;
	class Movement;
	class Phase;
	class Condition;
	class Sprite;
	class Shield;
	//Boss Class Implementation
	class Boss : public GameObject
	{
	public:
		Boss() = default;
		Boss(const char* aImagePath, VECTOR2F aSpawnPosition, float aHealthAmount);
		Boss(const char* aImagePath, rapidjson::Value& aBossParameters);
		~Boss();

		void Update();

		bool CheckCurrentPhaseCondition();
		//Tänk på en ny lösning när du får tid
		bool GetCurrentPhaseHasPlayedOnce();
		bool CheckEnrageCondition();

		//Legacy Boss "Swedish Abilities"
		/*void SendInTheCaroleans(float anAmountOfCanonFodder);
		void ActivateWelfare(float aTaxAmount);
		float SellGuns(float aMoralLimit);
		bool ActPassive(float aInternationalNotoriety);
		void EnforceAlleMansRätt();*/
		
		void UpdateMovement(Movement* aMovement);

		void ActivateShield(Shield* aShield);

		void HitLogic(float aDamage);

		float GetTotalBossTime();
		VECTOR2F* GetPosition();
		std::vector<VECTOR2F> GetBulletSpawnPositions();
		
	protected:

	private:
		
		int myCurrentPhase;
		int myPhaseAmount;
		int myTotalFightTime;

		VECTOR2F myPosition;
		
		Movement* myMovement;

		HealthBar myHealthBar;
		Shield* myShield;
		std::vector<Condition*> myConditions;
		Condition* myEnrageCondition;
		std::vector<Phase*> myPhases;
		std::vector<VECTOR2F> myBulletSpawnPositions;
	};


}
