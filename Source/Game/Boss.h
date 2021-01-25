#pragma once
#include "GameObject.h"
namespace Studio
{
	//Forward Declaring Classes
	class RenderCommand;
	class Bullet;
	class Movement;

	class Boss : public GameObject
	{
	public:
		Boss();
		Boss(Tga2D::CSprite* aSprite, VECTOR2F aSpawnPosition);
		~Boss();

		void Update();

		//Boss "Actions" / "Abilities", Temp shell functions.
		void SpawnMinions();
		void ShootLaser();

		//Boss "Swedish Abilities"
		void SendInTheCaroleans(float anAmountOfCanonFodder);
		void ActivateWelfare(float aTaxAmount);
		float SellGuns(float aMoralLimit);
		bool ActPassive(float aInternationalNotoriety);
		void EnforceAlleMansRätt();
		
		VECTOR2F GetPosition();
		


	protected:

	private:
		VECTOR2F myPosition;

		int myPhaseCount;
	};


}
