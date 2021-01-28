#include "stdafx.h"
#include "Boss.h"
#include "Timer.h"
#include "MovementBobbing.h"
#include "RendererAccessor.h"
#include "Renderer.h"
namespace Studio
{
	Boss::Boss() :
		GameObject(nullptr),
		myHealthBar(nullptr, {0.0f, 0.0f})
	{
	}

	Boss::Boss(const char* aImagePath, VECTOR2F aSpawnPosition, float aHealthAmount) :
		Boss::GameObject(aImagePath, aHealthAmount),
		myHealthBar("", { 700.0f, 100.0f })
	{
		myPosition = aSpawnPosition;
		myCurrentPhase = 0;
		myPhase1Condition = 0.8f;
		myPhase2Condition = 0.35f;
		SAFE_CREATE(myMovement, MovementBobbing(&myPosition, 20.0f, 200.0f));
		Boss::GameObject::GetCollider().AddCircleColliderObject(myPosition, 100.0f);
	}

	Boss::~Boss()
	{
	}

	void Boss::Update()
	{
		PhaseOne();
		//Phase 1 temp
		/*if (Boss::GameObject::GetCurrentHealth() / Boss::GameObject::GetMaxHealth() > myPhase1Condition)
		{
			PhaseOne();
		}*/
		////Phase 2 temp
		//if (Boss::GameObject::GetCurrentHealth() / Boss::GameObject::GetMaxHealth() <= myPhase1Condition && Boss::GameObject::GetCurrentHealth() / Boss::GameObject::GetMaxHealth() >= myPhase2Condition)
		//{
		//	PhaseTwo();
		//}
		////Phase 3 temp
		//else
		//{
		//	PhaseThree();
		//}
		myHealthBar.Update(GetHealth());

		RendererAccessor::GetInstance()->Render(*this);
	}

	void Boss::PhaseOne()
	{
		myMovement->Update();

		Boss::GameObject::Update(myPosition);

		//if (myTotalFightTime % myLaserCooldown == 0)
		//{
		//	ShootLaser();
		//}

		//UpdateHealthBar();
	}

	VECTOR2F Boss::GetPosition()
	{
		return myPosition;
	}

}
