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
	class EngineFlame;
	//Boss Class Implementation
	class Boss : public GameObject
	{
	public:
		Boss() = default;
		Boss(const char* aImagePath, rapidjson::Value& aBossParameters);
		~Boss();

		void Update();

		//Condition Checks for Phase transitions
		bool CheckCurrentPhaseCondition();
		bool GetCurrentPhaseHasPlayedOnce();
		bool CheckEnrageCondition();

		//Check if there is a transition on the current phase
		void CheckTransition();
		
		void UpdateMovement(Movement* aMovement);

		//Different "Cinematic" movements
		void PlayIntroMovement();
		void PlayTransition();
		bool ReturnToOriginalPosition();

		void ActivateShield(Shield* aShield);

		void HitLogic(float aDamage);

		void SetPosition(const VECTOR2F aPosition);

		float GetTotalBossTime();
		
		VECTOR2F* GetPosition();

		void ResetBoss();

	protected:

	private:
		
		int myCurrentPhase;
		int myPhaseAmount;
		int myTotalFightTime;
		int myTransitionPhase1 = 3;
		int myTransitionPhase2 = 6;
		

		bool myIntroMovementPlayed;
		bool myIsTransitioning;
		bool myTransitionAnimationPart1;
		bool myTransitionAnimationPart2;

		VECTOR2F myPosition;
		VECTOR2F myOriginalPosition = { 1500.0f , 540.0f};
		VECTOR2F myLateGameOffset = {0.0f, 0.0f};
		
		Movement* myMovement;
		Movement* myIntroMovement;

		Shield* myShield;
		HealthBar myHealthBar;
		Condition* myEnrageCondition;
		std::vector<Condition*> myConditions;
		std::vector<Phase*> myPhases;
	};


}
