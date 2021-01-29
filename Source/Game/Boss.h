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
	//Boss Class Implementation
	class Boss : public GameObject
	{
	public:
		Boss();
		Boss(const char* aImagePath, VECTOR2F aSpawnPosition, float aHealthAmount);
		Boss(const char* aImagePath, rapidjson::Value& aBossParameters);
		~Boss();

		void Update();

		//Phase One Functions
		void PhaseOne();

		//Legacy Boss "Swedish Abilities"
		/*void SendInTheCaroleans(float anAmountOfCanonFodder);
		void ActivateWelfare(float aTaxAmount);
		float SellGuns(float aMoralLimit);
		bool ActPassive(float aInternationalNotoriety);
		void EnforceAlleMansRätt();*/
		
		VECTOR2F GetPosition();
		
	protected:

	private:
		
		int myCurrentPhase;
		int myLaserCooldown;
		int myTotalFightTime;

		float myPhase1Condition;
		float myPhase2Condition;
		float myEnrageTimer;
		float myEnrageTimeCondition;

		VECTOR2F myPosition;
		
		Movement* myMovement;

		HealthBar myHealthBar;
		std::vector<Condition*> myConditions;
		std::vector<Phase*> myPhases;
		std::vector<VECTOR2F*> myBulletSpawnPositions;
	};


}
