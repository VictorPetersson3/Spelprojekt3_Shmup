#include "stdafx.h"
#include "Boss.h"

//Gameplay
#include "Timer.h"
#include "MovementBobbing.h"
#include "Condition.h"
#include "Condition_BelowHealth.h"
#include "Condition_DoOnce.h"
#include "Condition_Timed.h"
#include "Condition_Time.h"
#include "Phase.h"

//Json
#include "rapidjson/document.h"

//Rendering
#include "RendererAccessor.h"
#include "Renderer.h"
namespace Studio
{
	Boss::Boss() :
		GameObject(nullptr),
		myHealthBar(nullptr, { 0.0f, 0.0f })
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

	Boss::Boss(const char* aImagePath, rapidjson::Value& aBossParameters) :
		Boss::GameObject(aImagePath, 1000.0f),
		myHealthBar("", { 700.0f, 100.0f })
	{
		if (aBossParameters.HasMember("Conditions") && aBossParameters["Conditions"].IsArray())
		{
			auto conditions = aBossParameters["Conditions"].GetArray();
			for (size_t i = 0; i < conditions.Size(); i++)
			{
				if (conditions[i]["Type"].GetString() == "Timed")
				{
					myConditions.push_back(new Condition_Timed(conditions[i]));
				}
				if (conditions[i]["Type"].GetString() == "BelowHealth")
				{
					myConditions.push_back(new Condition_BelowHealth(conditions[i]));
				}
				if (conditions[i]["Type"].GetString() == "DoOnce")
				{
					myConditions.push_back(new Condition_DoOnce(conditions[i]));
				}
				if (conditions[i]["Type"].GetString() == "Time")
				{
					myConditions.push_back(new Condition_Time(conditions[i]));
				}
			}
		}

		if (aBossParameters.HasMember("Phases") && aBossParameters["Phases"].IsArray())
		{
			auto phases = aBossParameters["Phases"].GetArray();

			for (size_t i = 0; i < phases.Size(); i++)
			{
				myPhases.push_back(new Phase(phases[i]));
			}
		}

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
