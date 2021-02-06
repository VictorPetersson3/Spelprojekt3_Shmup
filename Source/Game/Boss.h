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
		Boss(const char* aImagePath, rapidjson::Value& aBossParameters);
		~Boss();

		void Update();

		bool CheckCurrentPhaseCondition();
		//Tänk på en ny lösning när du får tid
		bool GetCurrentPhaseHasPlayedOnce();
		bool CheckEnrageCondition();
		bool ShouldTransition();

		//Legacy Boss "Swedish Abilities"
		/*void SendInTheCaroleans(float anAmountOfCanonFodder);
		void ActivateWelfare(float aTaxAmount);
		float SellGuns(float aMoralLimit);
		bool ActPassive(float aInternationalNotoriety);
		void EnforceAlleMansRätt();*/
		
		void UpdateMovement(Movement* aMovement);
		void PlayIntroMovement();

		void ActivateShield(Shield* aShield);

		void HitLogic(float aDamage);

		float GetTotalBossTime();
		VECTOR2F* GetPosition();
		void SetPosition(const VECTOR2F aPosition);

		void ResetBoss();

		void PhaseTransition();

		
	protected:

	private:
		
		int myCurrentPhase;
		int myPhaseAmount;
		int myTotalFightTime;
		float myTargetXPosition = 1500.0f;
		float myTargetYPosition = 540.0f;

		bool myIntroMovementPlayed;
		bool myIsTransitioning;

		VECTOR2F myPosition;
		
		Movement* myMovement;
		Movement* myIntroMovement;

		HealthBar myHealthBar;
		Shield* myShield;
		std::vector<Condition*> myConditions;
		Condition* myEnrageCondition;
		std::vector<Phase*> myPhases;
	};


}
