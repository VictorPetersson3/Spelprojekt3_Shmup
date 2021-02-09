#include "stdafx.h"
#include "Boss.h"
#include "tga2d/sprite/sprite.h"
//Gameplay
#include "Timer.h"
#include "MovementBobbing.h"
#include "MovementWave.h"
#include "MovementStraight.h"
#include "Condition.h"
#include "Condition_BelowHealth.h"
#include "Condition_DoOnce.h"
#include "Condition_Timed.h"
#include "Condition_Time.h"
#include "Phase.h"
#include "Shield.h"

//Json
#include "rapidjson/document.h"

//Rendering
#include "RendererAccessor.h"
#include "Renderer.h"
namespace Studio
{
	Boss::Boss(const char* aImagePath, rapidjson::Value& aBossParameters) :
		Boss::GameObject(aImagePath, 200.0f),
		myHealthBar("Sprites/debugpixel.dds", { 700.0f, 100.0f }, 13)
	{
		mySpriteSheet.SetLayer(-1);
		GameObject::GetSpriteSheet().SetSizeRelativeToImage({ 1.0f,1.0f });
		myEnrageCondition = nullptr;
		myPosition = { 2050.0f, 540.0f };
		Boss::GameObject::GetCollider().AddCircleColliderObject({0,-20.0f }, 280.0f);
		Boss::GameObject::GetCollider().AddBoxColliderObject({ 220.0f, 257.0f }, { 135.0f, 305.0f });
		Boss::GameObject::GetCollider().AddBoxColliderObject({ -182.0f, 257.0f }, { 135.0f, 305.0f });
		if (aBossParameters.HasMember("Conditions") && aBossParameters["Conditions"].IsArray())
		{
			auto conditions = aBossParameters["Conditions"].GetArray();
			for (size_t i = 0; i < conditions.Size(); i++)
			{
				std::string type = conditions[i]["Type"].GetString();
				if (type == "Timed")
				{
					if (myEnrageCondition == nullptr)
					{
						myEnrageCondition = new Condition_Timed(conditions[i]);
					}
					else
					{
						printf_s("Timed Condition is only for enrage timer and you cant have two enrage Condition\n");
					}
				}
				else if (type.compare("BelowHealth") == 0)
				{
					myConditions.push_back(new Condition_BelowHealth(conditions[i]));
				}
				else if (type == "Once")
				{
					myConditions.push_back(new Condition_DoOnce(conditions[i]));
				}
				else if (type == "Time")
				{
					myConditions.push_back(new Condition_Time(conditions[i]));
				}
				else
				{
					printf("Condition type: %s Is corrupted or not implemented yet\n", conditions[i]["Type"].GetString());
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
		SAFE_CREATE(myIntroMovement, MovementStraight(&myPosition, 50.0f));

		myTotalFightTime = 0.0f;
		myCurrentPhase = 0;


		if (myEnrageCondition != nullptr)
		{
			myPhaseAmount = myPhases.size() - 1;
		}
		else
		{
			myPhaseAmount = myPhases.size();
		}
		myShield = nullptr;
		myMovement = nullptr;
		myIntroMovementPlayed = true;
		myIsTransitioning = false;
		SetGodMode(true);
	}

	Boss::~Boss()
	{
		SAFE_DELETE(myMovement);
		SAFE_DELETE(myIntroMovement);
		SAFE_DELETE(myEnrageCondition);
		for (Condition* condition : myConditions)
		{
			SAFE_DELETE(condition);
		}
		myConditions.clear();
		for (Phase* phase : myPhases)
		{
			SAFE_DELETE(phase);
		}
		myPhases.clear();
	}

	void Boss::Update()
	{

		if (!IsDead() && myIntroMovementPlayed && !myIsTransitioning)
		{

			myTotalFightTime += Timer::GetInstance()->TGetDeltaTime();
			if (CheckEnrageCondition())
			{
				myCurrentPhase = myPhaseAmount - 1;
			}


			myPhases[myCurrentPhase]->PlayModules(this);
			if (myMovement != nullptr)
			{
				myMovement->Update();
			}

			Boss::GameObject::Update(myPosition);
			myHealthBar.Update(GetHealth());

			//Plays the Modules in the current phase

			if (CheckCurrentPhaseCondition() && myCurrentPhase < myPhaseAmount - 1)
			{
				++myCurrentPhase;
				printf("Changed to Phase: %i\n", myCurrentPhase);
				if (ShouldTransition())
				{
					//TODO Call transition between phase sprites or animations not SpriteSwitch
					//SwitchSprite();
					myIsTransitioning = true;
				}
			}
			if (myShield != nullptr)
			{
				myShield->Update();
			}
			RendererAccessor::GetInstance()->Render(*this);
		}
		else if (!myIntroMovementPlayed)
		{
			PlayIntroMovement();
		}
		else if (myIsTransitioning)
		{
			PlayTransition();
		}
	}

	void Boss::UpdateMovement(Movement* aMovement)
	{
		if (myMovement != nullptr)
		{
			SAFE_DELETE(myMovement);
		}
		myMovement = aMovement;
	}

	void Boss::PlayIntroMovement()
	{
		myIntroMovement->Update();
		Boss::GameObject::Update(myPosition);
		if (myPosition.x <= myOriginalPosition.x)
		{
			myIntroMovementPlayed = true;
			SetGodMode(false);
		}
		RendererAccessor::GetInstance()->Render(*this);
	}

	void Boss::ActivateShield(Shield* aShield)
	{
		if (myShield == nullptr)
		{
			myShield = aShield;
			//myShield->GetHealthBar()->SetSizeX(450.0f);
			//myShield->GetHealthBar()->SetSizeY(25.0f);
		}
	}

	void Boss::HitLogic(float aDamage)
	{
		if (myShield == nullptr)
		{
			TakeDamage(aDamage);
		}
		else
		{
			myShield->HitLogic(aDamage);
			if (myShield->IsDead())
			{
				SAFE_DELETE(myShield);
			}
		}

	}

	bool Boss::CheckCurrentPhaseCondition()
	{
		return myConditions.at(myCurrentPhase)->IsDone(*this);
	}

	bool Boss::GetCurrentPhaseHasPlayedOnce()
	{
		return myPhases[myCurrentPhase]->HavePlayedOnce();
	}

	bool Boss::CheckEnrageCondition()
	{
		if (myEnrageCondition != nullptr)
		{
			return myEnrageCondition->IsDone(*this);
		}
		else
		{
			return false;
		}
	}

	bool Boss::ShouldTransition()
	{
		if (myCurrentPhase == 3 || myCurrentPhase == 6)
		{
			return true;
		}
		return false;
	}

	void Boss::PlayTransition()
	{
		SetGodMode(true);
		VECTOR2F aDirection = myOriginalPosition - myPosition;

		if (aDirection.y > myOriginalPosition.y - 100.0f && aDirection.y < myOriginalPosition.y + 100.0f)
		{
			SwitchSprite();
			myIsTransitioning = false;
			SetGodMode(false);
		}
		else
		{
			myPosition += aDirection * Timer::GetInstance()->TGetDeltaTime();
		}
		Boss::GameObject::Update(myPosition);
		RendererAccessor::GetInstance()->Render(*this);
		//TODO add playing of correct transition
	}

	void Boss::SwitchSprite()
	{
		if (myCurrentPhase == 3)
		{
			mySpriteSheet.SetImagePath("Sprites/assets/enemies/boss/globePhase_02.dds");
		}
		if (myCurrentPhase == 6)
		{
			mySpriteSheet.SetImagePath("Sprites/assets/enemies/boss/globePhase_03.dds");
		}
	}

	float Boss::GetTotalBossTime()
	{
		return myTotalFightTime;
	}

	VECTOR2F* Boss::GetPosition()
	{
		return &myPosition;
	}

	void Boss::SetPosition(const VECTOR2F aPosition)
	{
		myPosition = aPosition;
	}

	void Boss::ResetBoss()
	{
		for (Phase* phase : myPhases)
		{
			phase->ResetPhase();
		}
		if (myShield != nullptr)
		{
			SAFE_DELETE(myShield);
		}
		myHealth.ResetHealth();
		SetGodMode(true);
		myPosition = { 2000.0f, 540.0f };
		myIntroMovementPlayed = false;
		myTotalFightTime = 0.0f;
		myCurrentPhase = 0;
		mySpriteSheet.SetImagePath("Sprites/assets/enemies/boss/globePhase_01.dds");
	}

}
