#include "stdafx.h"
#include "Boss.h"
#include "tga2d/sprite/sprite.h"
//Gameplay
#include "Timer.h"
#include "MovementBobbing.h"
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
	/*Boss::Boss() :
		GameObject(nullptr),
		myHealthBar(nullptr, { 0.0f, 0.0f })
	{
	}*/

	Boss::Boss(const char* aImagePath, VECTOR2F aSpawnPosition, float aHealthAmount) :
		Boss::GameObject(aImagePath, aHealthAmount),
		myHealthBar("Sprites/debugpixel.dds", { 700.0f, 100.0f }, 13)
	{
		myPosition = aSpawnPosition;
		myCurrentPhase = 0;
		myEnrageCondition = nullptr;
		SAFE_CREATE(myMovement, MovementBobbing(&myPosition, 20.0f, 200.0f));
		Boss::GameObject::GetCollider().AddCircleColliderObject(myPosition, 200.0f);
	}

	Boss::Boss(const char* aImagePath, rapidjson::Value& aBossParameters) :
		Boss::GameObject(aImagePath, 1000.0f),
		myHealthBar("Sprites/debugpixel.dds", { 700.0f, 100.0f }, 13)
	{
		GameObject::GetSpriteSheet().SetSizeRelativeToImage({0.5f, 0.5f});
		myEnrageCondition = nullptr;
		myPosition = { 1500.0f, 520.0f };
		Boss::GameObject::GetCollider().AddCircleColliderObject(myPosition, 125.0f);
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
			myCurrentPhase = 0;
			myPhaseAmount = myPhases.size();
		}
		myMovement = nullptr;
		myTotalFightTime = 0.0f;
		myShield = nullptr;
	}

	Boss::~Boss()
	{
		SAFE_DELETE(myMovement);
		SAFE_DELETE(myEnrageCondition);
		myConditions.clear();
		myPhases.clear();
	}

	void Boss::Update()
	{
		if (!IsDead())
		{
			myTotalFightTime += Timer::GetInstance()->TGetDeltaTime();
			if (myMovement != nullptr)
			{
				myMovement->Update();
			}

			Boss::GameObject::Update(myPosition);
			myHealthBar.Update(GetHealth());


			myPhases[myCurrentPhase]->PlayModules(this);

			if (CheckCurrentPhaseCondition() && myCurrentPhase < myPhaseAmount - 2)
			{
				++myCurrentPhase;
				printf("Changed to Phase: %i\n", myCurrentPhase);
			}
			if (CheckEnrageCondition())
			{
				myCurrentPhase = myPhaseAmount - 1;
			}
			if (myShield != nullptr)
			{
				myShield->Update();
			}
			RendererAccessor::GetInstance()->Render(*this);
		}
	}

	void Boss::UpdateMovement(Movement* aMovement)
	{
		SAFE_DELETE(myMovement);
		myMovement = aMovement;
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

			//Test for some feedback on boss hit
			auto color = GameObject::GetSpriteSheet().GetSprite()->GetColor();
			GameObject::GetSpriteSheet().GetSprite()->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
			GameObject::GetSpriteSheet().GetSprite()->SetColor(color);
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

	float Boss::GetTotalBossTime()
	{
		return myTotalFightTime;
	}

	VECTOR2F* Boss::GetPosition()
	{
		return &myPosition;
	}

	std::vector<VECTOR2F> Boss::GetBulletSpawnPositions()
	{
		return myBulletSpawnPositions;
	}

}
