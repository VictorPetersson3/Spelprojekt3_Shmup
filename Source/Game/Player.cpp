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

#define SPRITESHEET GameObject::GetSpriteSheet()

namespace Studio
{
	Player::Player(const char* aImagePath) :
		Player::GameObject(aImagePath),
		myEngineFlame("sprites/assets/player/Flame.dds", { 1, 4 }, { 300 - 48, 540 - 9 })
	{
		SPRITESHEET.SetAmountOfFrames({ 1, 8 });
		myEngineFlame.GetSpriteSheet().SetLayer(-1);
		myFrames = { 1, 8 };
		myPosition = { 300, 540 };
		mySpeed = 0;
		myShootCooldown = 0.0f;
		myAnimationTime = 0;
		myAnimationTurnSpeed = 0.075;
		myCurrentFlame = 2;
		GetCollider().AddCircleColliderObject(myPosition, 20);
	}

	Player::~Player()
	{
	}

	void Player::Update()
	{
		if (!IsDead())
		{
			Movement();

			Player::GameObject::Update(myPosition);

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
			myShootCooldown += Timer::GetInstance()->TGetDeltaTime();
			if (GetAsyncKeyState(VK_SPACE) && myShootCooldown > 0.1f)
			{
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", myPosition);
				myShootCooldown = 0;
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
			mySpeed = 200;
		}
		else
		{
			mySpeed = 300; //Temp value, change to default value provided by json when added
		}
		
		if (wKey && myPosition.y > 0)
		{
			if (myIsAnimatingDown || !myIsAnimating)
			{
				myIsAnimatingDown = false;
				GameObject::GetSpriteSheet().PlayAnimationInRange(myAnimationTurnSpeed, { 1, 5 }, { 1, 7 });
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
				GameObject::GetSpriteSheet().PlayAnimationInRange(myAnimationTurnSpeed, { 1, 2 }, { 1, 4 });
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
				Player::GameObject::SetFrame({ 1, 1 });
			}
		}
		if (!aKey && !dKey)
		{
			myCurrentFlame = 2;
		}
		myEngineFlame.Update(myCurrentFlame, { myPosition.x - 48, myPosition.y - 9 });
		//Spacebar
		if (Studio::InputManager::GetInstance()->IsKeyDown(VK_SPACE))
		{
			Shoot();
		}
	}
}

