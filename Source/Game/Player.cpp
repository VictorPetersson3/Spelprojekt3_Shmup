#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "InputManager.h"
#include "tga2d/sprite/sprite.h"
#include "Renderer.h"
#include "RendererAccessor.h"
#include "CoinAccessor.h"
#include "ScoreAccessor.h"
#include "LevelAccessor.h"
#include "Coin.h"
#include "Timer.h"
#include "Player_JsonParser.h"


#define SPRITESHEET GameObject::GetSpriteSheet()

namespace Studio
{
	Player::Player(Player_JsonParser* somePlayerData) :
		Player::GameObject(somePlayerData->GetImagePath(), 4.0f),
		myEngineFlame(somePlayerData->GetFlameImagePath().c_str(), somePlayerData->GetAmountOfFlameFrames(), { 300 - 48, 540 - 9 }),
		myPlayerData(somePlayerData)
	{
		SPRITESHEET.SetImagePath(myPlayerData->GetImagePath());
		SPRITESHEET.SetAmountOfFrames(somePlayerData->GetAmountOfFrames());
		SPRITESHEET.SetLayer(somePlayerData->GetLayer());
		myEngineFlame.GetSpriteSheet().SetLayer(somePlayerData->GetLayer() -1);
		myPosition = { 300, 540 };
		myAnimationTurnSpeed = 0.075f;
		myCurrentFlame = 2.f;
		myRapidFireCurrentlyActiveTime = 0.f;
		myTimeSinceLastShot = 0.f;
		mySpeed = somePlayerData->GetMinSpeed();
		myRapidFireMaxActiveTime = somePlayerData->GetRapidFireMaxActiveTime();
		myRapidFireCurrentCooldown = somePlayerData->GetRapidFireMaxCooldown();
		GetCollider().AddCircleColliderObject(myPosition, 20);
	}

	Player::~Player()
	{
		delete myPlayerData;
		myPlayerData = nullptr;
	}

	void Player::Update()
	{
		if (!IsDead())
		{
			Movement();

			Player::GameObject::Update(myPosition);

			Shoot();

			RapidFireLogic(myPlayerData->GetCDReductionPercentage());

			Studio::RendererAccessor::GetInstance()->Render(*this);
		}

		auto& worldCoins = CoinAccessor::GetInstance()->GetWorldCoins();

		for (int i = 0; i < worldCoins.size(); i++)
		{
			if (worldCoins[i]->Intersects(*this))
			{
				ScoreAccessor::GetInstance()->AddCoinScore(1);
				worldCoins.erase(worldCoins.begin() + i);

				printf_s("bruh");
			}
		}
	}

	void Player::Shoot()
	{
		myTimeSinceLastShot += Timer::GetInstance()->TGetDeltaTime();
		if (GetAsyncKeyState(VK_SPACE) && myTimeSinceLastShot > myPlayerData->GetShootCoolDown())
		{
    		Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", myPosition);
			myTimeSinceLastShot = 0.f;
		}
	}

	void Player::Movement()
	{
		bool wKey = Studio::InputManager::GetInstance()->IsKeyDown('W');
		bool aKey = Studio::InputManager::GetInstance()->IsKeyDown('A');
		bool sKey = Studio::InputManager::GetInstance()->IsKeyDown('S');
		bool dKey = Studio::InputManager::GetInstance()->IsKeyDown('D');
		//W

		if ((wKey && aKey) || (wKey && dKey) || (sKey && aKey) || (sKey && dKey))
		{
			mySpeed = myPlayerData->GetMinSpeed();
		}
		else
		{
			mySpeed = myPlayerData->GetMaxSpeed(); 
		}
		
		if (wKey && myPosition.y > 0)
		{
			if (myIsAnimatingDown || !myIsAnimating)
			{
				myIsAnimatingDown = false;
				SPRITESHEET.PlayAnimationInRange(myPlayerData->GetAnimationTurnSpeed(), myPlayerData->GetUpAnimationRange().first, myPlayerData->GetUpAnimationRange().second);
				myIsAnimatingUp = true;
				myIsAnimating = true;
			}
			

			myPosition.y -= mySpeed * Timer::GetInstance()->TGetDeltaTime();
		}
		//A
		if (aKey && myPosition.x > 0)
		{
			myPosition.x -= mySpeed * Timer::GetInstance()->TGetDeltaTime();
			myCurrentFlame = 1;
		}
		//S
		if (sKey && myPosition.y < 1080)
		{
			if (myIsAnimatingUp || !myIsAnimating)
			{
				myIsAnimatingUp = false;
				SPRITESHEET.PlayAnimationInRange(myPlayerData->GetAnimationTurnSpeed(), myPlayerData->GetDownAnimationRange().first, myPlayerData->GetDownAnimationRange().second);
				myIsAnimatingDown = true;
				myIsAnimating = true;
			}
			
			myPosition.y += mySpeed * Timer::GetInstance()->TGetDeltaTime();
		}
		//D
		if (dKey && myPosition.x < 1920)
		{
			myPosition.x += mySpeed * Timer::GetInstance()->TGetDeltaTime();
			myCurrentFlame = 3;
		}
		if (!sKey && !wKey)
		{

			if (myIsAnimating)
			{
				if (myIsAnimatingDown)
				{
					if (!myIsRebounding)
					{
						SPRITESHEET.ReverseAndStartAnimation();
						myIsRebounding = true;
					}
					else
					{
						if (!SPRITESHEET.IsAnimating())
						{
							myIsAnimating = false;
						}
					}
				}
				if (myIsAnimatingUp)
				{
					if (!myIsRebounding)
					{
						SPRITESHEET.ReverseAndStartAnimation();
						myIsRebounding = true;
					}
					else
					{
						if (!SPRITESHEET.IsAnimating())
						{
							myIsAnimating = false;
						}
					}
				}
			}
			else
			{
				myIsAnimatingUp = false;
				myIsAnimatingDown = false;
				myIsAnimating = false;
				myIsRebounding = false;
				Player::GameObject::SetFrame(myPlayerData->GetIdleAnimationRange().first);
			}
		}
		if (!aKey && !dKey)
		{
			myCurrentFlame = 2;
		}
		myEngineFlame.Update(myCurrentFlame, { myPosition.x - 48, myPosition.y - 9 });
		//Spacebar
		
	}
	void Player::RapidFireLogic(float aCDReductionPercentage)
	{
		printf_s("%f\n", myPlayerData->GetShootCoolDown());

		ActivateRapidFire(aCDReductionPercentage);

		RapidFireIsActive();

		DeactivateRapidFire(aCDReductionPercentage);

	}
	//Check if key is pressed and cooldown has expired
	void Player::ActivateRapidFire(float aCDReductionPercentage)
	{
		if (InputManager::GetInstance()->IsKeyPressed('1') && myRapidFireCurrentCooldown > myPlayerData->GetRapidFireMaxCooldown())
		{
			myRapidFireCurrentCooldown = 0.f;

			myRapidFireIsActive = true;

			myPlayerData->SetShootCoolDown(myPlayerData->GetShootCoolDown() * (1 - aCDReductionPercentage * 0.01));
		}
	}
	//Check if Rapidfire is active
	void Player::RapidFireIsActive()
	{
		if (myRapidFireIsActive)
		{
			myRapidFireCurrentlyActiveTime += Timer::GetInstance()->TGetDeltaTime();
		}
		else
		{
			myRapidFireCurrentlyActiveTime = 0.f;

			myRapidFireCurrentCooldown += Timer::GetInstance()->TGetDeltaTime();
		}
	}
	//check if RapidFire is active for as long as it is allowed to be active, then deactive itand bring back baseline attack speed.
	void Player::DeactivateRapidFire(float aCDReductionPercentage)
	{
		if (myRapidFireCurrentlyActiveTime > myPlayerData->GetRapidFireMaxActiveTime())
		{
			myRapidFireIsActive = false;

			myPlayerData->SetShootCoolDown(myPlayerData->GetShootCoolDown() * (1 - aCDReductionPercentage * 0.01));
		}
	}
}

