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
#include "LevelAccessor.h"
#include "AudioManagerAccesor.h"
#include "AudioManager.h"
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

		mySpriteSheet.SetAmountOfFrames({ 8.0f, 8.0f });
		mySpriteSheet.LoopAnimationInRange(0.0833f, { 1, 1 }, { 6, 1 });
		//mySpriteSheet.SetSize({ 100, 100 });

		//in case there is no enrage condition
		myEnrageCondition = nullptr;

		//CollisionObjects
		Boss::GameObject::GetCollider().AddCircleColliderObject({ 20.0f, 0.0f }, 280.0f);
		Boss::GameObject::GetCollider().AddCircleColliderObject({ -20.0f,-280.0f }, 25.0f);
		Boss::GameObject::GetCollider().AddBoxColliderObject({ 170.0f, 180.0f }, { 135.0f, 200.0f });
		Boss::GameObject::GetCollider().AddBoxColliderObject({ -190.0f, 180.0f }, { 135.0f, 200.0f });
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
				if (type.compare("BelowHealth") == 0)
				{
					myConditions.push_back(new Condition_BelowHealth(conditions[i]));
				}
				if (type == "Once")
				{
					myConditions.push_back(new Condition_DoOnce(conditions[i]));
				}
				if (type == "Time")
				{
					myConditions.push_back(new Condition_Time(conditions[i]));
				}
				//else
				//{
				//	printf("Condition type: %s Is not implemented\n", conditions[i]["Type"].GetString());
				//}
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
		
		SAFE_CREATE(myIntroMovement, MovementStraight(&myPosition, 55.0f));

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
		myTransitionAnimationPart1 = false;
		myTransitionAnimationPart2 = false;
		myIsTransitioning = false;
		SetGodMode(true);

		myTotalFightTime = 0.0f;
		myCurrentPhase = 0;

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

		if (!IsDead())
		{
			if (!myIntroMovementPlayed)
			{
				SetGodMode(true);

				PlayIntroMovement();
			}
			else if (myIsTransitioning)
			{
				SetGodMode(true);

				PlayTransition();
			}
			else
			{
				myTotalFightTime += Timer::GetInstance()->TGetDeltaTime();
				if (CheckEnrageCondition())
				{
					myCurrentPhase = myPhaseAmount - 1;
				}

				if (myMovement != nullptr)
				{
					myMovement->Update();
				}

				myPhases[myCurrentPhase]->PlayModules(this);

				if (CheckCurrentPhaseCondition() && myCurrentPhase < myPhaseAmount - 1)
				{
					CheckTransition();
				}

				myHealthBar.Update(GetHealth());
				if (myShield != nullptr)
				{
					myShield->Update({ myPosition.x + myLateGameOffset.x, myPosition.y + myLateGameOffset.y });
				}
			}
			//Update to render everything
			RendererAccessor::GetInstance()->Render(*this);
			Boss::GameObject::Update(myPosition);
			myCollider.Update({ myPosition.x + myLateGameOffset.x, myPosition.y + myLateGameOffset.y });
		}
	}

	void Boss::ActivateShield(Shield* aShield)
	{
		if (myShield == nullptr)
		{
			myShield = aShield;
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
		if (myPosition.x <= myOriginalPosition.x)
		{
			myIntroMovementPlayed = true;
			SetGodMode(false);
		}
	}

	void Boss::CheckTransition()
	{
		++myCurrentPhase;
		printf("Changed to Phase: %i\n", myCurrentPhase);
		if (LevelAccessor::GetInstance()->IsLaserFiring())
		{
			myPhases[myCurrentPhase - 1]->ResetPhase();
		}
		if (myCurrentPhase == myTransitionPhase1)
		{
			myIsTransitioning = true;
			mySpriteSheet.PlayAnimationInRange(0.0833f, { 1, 2 }, { 6, 2 });
			myLateGameOffset = { 0.0f, -75.0f };
		}
		else if (myCurrentPhase == myTransitionPhase2)
		{
			myIsTransitioning = true;
			mySpriteSheet.PlayAnimationInRange(0.0833f, { 1, 4 }, { 6, 4 });
			myTransitionAnimationPart1 = true;
		}
	}

	void Boss::PlayTransition()
	{
		if (ReturnToOriginalPosition())
		{
			myIsTransitioning = false;
			SetGodMode(false);
			if (myCurrentPhase == myTransitionPhase1)
			{
				mySpriteSheet.LoopAnimationInRange(0.0833f, { 1, 3 }, { 6, 3 });
			}
			if (myCurrentPhase == myTransitionPhase2)
			{
				mySpriteSheet.LoopAnimationInRange(0.0833f, { 1, 7 }, { 6, 7 });
			}
		}
		//TODO add playing of correct transition
	}

	bool Boss::ReturnToOriginalPosition()
	{
		VECTOR2F aDirection = myOriginalPosition - myPosition;
		if (myCurrentPhase == myTransitionPhase2 && myTransitionAnimationPart1 && !myTransitionAnimationPart2 && !mySpriteSheet.IsAnimating())
		{
			mySpriteSheet.PlayAnimationInRange(0.0833f, { 1, 5 }, { 6, 5 });
			myTransitionAnimationPart1 = false;
			myTransitionAnimationPart2 = true;
			myPosition += aDirection * 2 * Timer::GetInstance()->TGetDeltaTime();
		}
		else if (myCurrentPhase == myTransitionPhase2 && !myTransitionAnimationPart1 && myTransitionAnimationPart2 && !mySpriteSheet.IsAnimating())
		{
			mySpriteSheet.PlayAnimationInRange(0.0833f, { 1, 6 }, { 6, 6 });
			myTransitionAnimationPart2 = false;
			myPosition += aDirection * 2 * Timer::GetInstance()->TGetDeltaTime();
		}
		else if (aDirection.y < 10.0f && aDirection.y > -10.0f && !mySpriteSheet.IsAnimating() && !myTransitionAnimationPart1 && !myTransitionAnimationPart2)
		{
			return true;
		}
		else
		{
			myPosition += aDirection * 2 * Timer::GetInstance()->TGetDeltaTime();
		}
		return false;
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
		return false;
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
		myPosition = { 2300.0f, 540.0f };
		myIntroMovementPlayed = false;
		myIsTransitioning = false;
		myTransitionAnimationPart1 = false;
		myTransitionAnimationPart2 = false;
		myTotalFightTime = 0.0f;
		myCurrentPhase = 0;
		mySpriteSheet.LoopAnimationInRange(0.0833f, { 1, 1 }, { 6, 1 });
		myLateGameOffset = { 0.0f, 0.0f };
		AudioManagerAccessor::GetInstance()->StopAllSounds();
		AudioManagerAccessor::GetInstance()->Play2D("Audio/PiratesOfTheBaltic_-_The_Might_of_the_Three_Crowns.mp3", true, 0.1f);
	}

}
