#pragma once
#include "GameObject.h"
#include "Enums.h"
#include "HealthBar.h"
namespace Studio
{
	//Forward Declaring Classes
	class RenderCommand;
	class Bullet;
	class Movement;
	
	//Boss Class Implementation
	class Boss : public GameObject
	{
	public:
		Boss();
		Boss(const char* aImagePath, VECTOR2F aSpawnPosition, float aHealthAmount);
		~Boss();

		void Update();

		//Phase One Functions
		void PhaseOne();
		void Shoot();
		void GetSpawnEnemiesCooldown();


		//Phase Two Functions
		void PhaseTwo();
		void ShootLaser();

		//Phase Three Functions
		void PhaseThree();

		//Shared Phase Functions
		void UpdateHealthBar();

		//Boss "Swedish Abilities"
		void SendInTheCaroleans(float anAmountOfCanonFodder);
		void ActivateWelfare(float aTaxAmount);
		float SellGuns(float aMoralLimit);
		bool ActPassive(float aInternationalNotoriety);
		void EnforceAlleMansRätt();
		
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
	};


}
