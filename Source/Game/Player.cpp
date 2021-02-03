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
		myBounceBackTime = 0.25;

		myAmountOfProjectiles = 1;

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
			if (InputManager::GetInstance()->IsKeyPressed('2'))
			{
				UpgradeT1(Enums::Tier1Upgrades::BasicAttackSpeed);
			}
			if (InputManager::GetInstance()->IsKeyPressed('3'))
			{
				UpgradeT2(Enums::Tier2Upgrades::BasicAttackSpeed);

			}
			if (InputManager::GetInstance()->IsKeyPressed('4'))
			{
				UpgradeT3(Enums::Tier3Upgrades::BasicAttackSpeed);
			}
			printf_s("%f", myPlayerData->GetShootCoolDown());
			Movement();

			Player::GameObject::Update(myPosition + myDirection);

			Shoot();

			RapidFireLogic();

			Studio::RendererAccessor::GetInstance()->Render(*this);
		}

		auto& worldCoins = CoinAccessor::GetInstance()->GetWorldCoins();

		for (int i = 0; i < worldCoins.size(); i++)
		{
			if (worldCoins[i]->Intersects(*this))
			{
				ScoreAccessor::GetInstance()->AddCoinScore(1);
				worldCoins.erase(worldCoins.begin() + i);
			}
		}
		//GameObject::GetCollider().Render();
	}

	void Player::Shoot()
	{
		myTimeSinceLastShot += Timer::GetInstance()->TGetDeltaTime();
		if (GetAsyncKeyState(VK_SPACE) && myTimeSinceLastShot > myPlayerData->GetShootCoolDown())
		{
			if (myAmountOfProjectiles == 1)
			{
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y - 5.f });

			}
			else if (myAmountOfProjectiles == 2)
			{
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y - 20.f });
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y + 10.f });

			}
			else if (myAmountOfProjectiles == 3)
			{
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y - 5.f });
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y - 30.f });
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y + 20.f });
			}
			myTimeSinceLastShot = 0.f;
		}
	}

	void Player::Bounce(const Tga2D::Vector2f aObjectPosition)
	{
		//myBounceDirection = myDirection * -1.0f;
		myBounceDirection = aObjectPosition - myPosition;
		myBounceDirection.Normalize();
		myBounceDirection = myBounceDirection * -1;
		myDirection = myBounceDirection;
		myHasCollided = true;
	}

	const Tga2D::Vector2f Player::GetDirection() const
	{
		return myDirection;
	}
	void Player::UpgradeRapidFire(Enums::RapidFireUpgrades aRapidFireUpgrade)
	{
		switch (aRapidFireUpgrade)
		{
		case Studio::Enums::RapidFireUpgrades::CooldownT1:
			myPlayerData->UpgradeRapidFireCooldownT1();
			break;
		case Studio::Enums::RapidFireUpgrades::AttackSpeedT1:
			myPlayerData->UpgradeRapidFireAttackSpeedT1();
			break;
		case Studio::Enums::RapidFireUpgrades::AttackSpeedT2:
			myPlayerData->UpgradeRapidFireAttackSpeedT2();
			break;
		case Studio::Enums::RapidFireUpgrades::DurationT1:
			myPlayerData->UpgradeRapidFireDurationT1();
			break;
		case Studio::Enums::RapidFireUpgrades::DurationT2:
			myPlayerData->UpgradeRapidFireDurationT2();
			break;
		case Studio::Enums::RapidFireUpgrades::PenetratingT3:
			myHasPurchasedPenetratingRounds = true;
			break;
		}
	}

	void Player::UpgradeT1(Enums::Tier1Upgrades aTier1Upgrade)
	{
		switch (aTier1Upgrade)
		{
		case Studio::Enums::Tier1Upgrades::RapidFireCooldown:
			myPlayerData->UpgradeRapidFireCooldownT1();
			break;
		case Studio::Enums::Tier1Upgrades::RapidFireAttackSpeed:
			myPlayerData->UpgradeRapidFireAttackSpeedT1();
			break;
		case Studio::Enums::Tier1Upgrades::RapidFireDuration:
			myPlayerData->UpgradeRapidFireDurationT1();
			break;
		case Studio::Enums::Tier1Upgrades::MovementSpeed:
			break;
		case Studio::Enums::Tier1Upgrades::BasicAttackSpeed:
			myPlayerData->UpgradeBasicAttackSpeedT1();
			break;
		case Studio::Enums::Tier1Upgrades::MissileExplosionRadius:
			break;
		case Studio::Enums::Tier1Upgrades::MissileCooldown:
			break;
		case Studio::Enums::Tier1Upgrades::MissileDamage:
			break;
		case Studio::Enums::Tier1Upgrades::ShieldDuration:
			break;
		case Studio::Enums::Tier1Upgrades::ShieldHealth:
			break;
		case Studio::Enums::Tier1Upgrades::ShieldCooldown:
			break;
		}
	}

	void Player::UpgradeT2(Enums::Tier2Upgrades aTier2Upgrade)
	{
		switch (aTier2Upgrade)
		{
		case Studio::Enums::Tier2Upgrades::RapidFireAttackSpeed:
			myPlayerData->UpgradeRapidFireAttackSpeedT2();
			break;
		case Studio::Enums::Tier2Upgrades::RapidFireDuration:
			myPlayerData->UpgradeRapidFireDurationT2();
			break;
		case Studio::Enums::Tier2Upgrades::BasicAttackSpeed:
			myPlayerData->UpgradeBasicAttackSpeedT2();
			break;
		case Studio::Enums::Tier2Upgrades::BasicAttackAdditionalProjectile:
			break;
		case Studio::Enums::Tier2Upgrades::MissileExplosionRadius:
			break;
		case Studio::Enums::Tier2Upgrades::MissileCooldown:
			break;
		case Studio::Enums::Tier2Upgrades::MissileDamage:
			break;
		case Studio::Enums::Tier2Upgrades::ShieldDuration:
			break;
		case Studio::Enums::Tier2Upgrades::ShieldHealth:
			break;
		case Studio::Enums::Tier2Upgrades::ShieldCooldown:
			break;
		}
	}

	void Player::UpgradeT3(Enums::Tier3Upgrades aTier3Upgrade)
	{
		switch (aTier3Upgrade)
		{
		case Studio::Enums::Tier3Upgrades::RapidFirePenetrating:
			myHasPurchasedPenetratingRounds = true;
			break;
		case Studio::Enums::Tier3Upgrades::BasicAttackSpeed:
			myPlayerData->UpgradeBasicAttackSpeedT3();
			break;
		case Studio::Enums::Tier3Upgrades::MissileCluster:
			break;
		case Studio::Enums::Tier3Upgrades::ShieldExplosion:
			break;
		}
	}

	bool Player::HasPenetratingRounds()
	{
		return myHasPenetratingRounds;
	}

	const bool Player::GetHasCollided() const
	{
		return myHasCollided;
	}

	void Player::Movement()
	{
		if (InputManager::GetInstance()->IsKeyPressed('4'))
		{
			UpgradeRapidFire(Enums::RapidFireUpgrades::PenetratingT3);
		}
		bool wKey = InputManager::GetInstance()->IsKeyDown('W');
		bool aKey = InputManager::GetInstance()->IsKeyDown('A');
		bool sKey = InputManager::GetInstance()->IsKeyDown('S');
		bool dKey = InputManager::GetInstance()->IsKeyDown('D');
		//W
		myDirection = myDirection.Zero;
		if (myHasCollided)
		{
			myCurrentFlame = 1;
			if (mySpeed >= myPlayerData->GetMaxSpeed() + 300)
			{
				mySpeed = myPlayerData->GetMaxSpeed() + 300;
			}
			else
			{
				mySpeed += myPlayerData->GetAcceleration() * 5;
			}
			myCurrentBounceTime += Timer::GetInstance()->TGetDeltaTime();
			myDirection = myBounceDirection;
			if (myCurrentBounceTime >= myBounceBackTime)
			{
				myHasCollided = false;
				myCurrentBounceTime = 0;
				myBounceDirection = myBounceDirection.Zero;
			}
		}
		else
		{
			myHasCollided = false;
			myCurrentBounceTime = 0;
			myBounceDirection = myBounceDirection.Zero;

			bool wKey = Studio::InputManager::GetInstance()->IsKeyDown('W');
			bool aKey = Studio::InputManager::GetInstance()->IsKeyDown('A');
			bool sKey = Studio::InputManager::GetInstance()->IsKeyDown('S');
			bool dKey = Studio::InputManager::GetInstance()->IsKeyDown('D');
			//W
			/*if ((wKey && aKey) || (wKey && dKey) || (sKey && aKey) || (sKey && dKey))
			{

				if (mySpeed <= myPlayerData->GetMinSpeed())
				{
					mySpeed = myPlayerData->GetMinSpeed();
				}
				else
				{
					mySpeed -= myAcceleration * 2;
				}
			}
			else
			{
				if (mySpeed >= myPlayerData->GetMaxSpeed())
				{
					mySpeed = myPlayerData->GetMaxSpeed();
				}
				else
				{
					mySpeed += myAcceleration;
				}
			}*/

			if (!wKey && !aKey && !sKey && !dKey)
			{
				if (mySpeed <= myPlayerData->GetMinSpeed())
				{
					mySpeed = myPlayerData->GetMinSpeed();
				}
				else
				{
					mySpeed -= myPlayerData->GetAcceleration();
				}
			}
			else
			{
				if (mySpeed >= myPlayerData->GetMaxSpeed())
				{
					mySpeed = myPlayerData->GetMaxSpeed();
				}
				else
				{
					mySpeed += myPlayerData->GetAcceleration();
				}
			}
			printf("Player Speed: %f\n", mySpeed);
			if (wKey && myPosition.y > 0)
			{
				if (myIsAnimatingDown || !myIsAnimating)
				{
					myIsAnimatingDown = false;
					SPRITESHEET.PlayAnimationInRange(myPlayerData->GetAnimationTurnSpeed(), myPlayerData->GetUpAnimationRange().first, myPlayerData->GetUpAnimationRange().second);
					myIsAnimatingUp = true;
					myIsAnimating = true;
				}
				myDirection.y -= mySpeed * Timer::GetInstance()->TGetDeltaTime();
			}
			//A
			if (aKey && myPosition.x > 0)
			{
				myDirection.x -= mySpeed * Timer::GetInstance()->TGetDeltaTime();
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

				myDirection.y += mySpeed * Timer::GetInstance()->TGetDeltaTime();
			}
			//D
			if (dKey && myPosition.x < 1920)
			{
				myDirection.x += mySpeed * Timer::GetInstance()->TGetDeltaTime();
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
			//Spacebar
		}
		myPosition += myDirection.Normalize() * mySpeed * Timer::GetInstance()->TGetDeltaTime();
		myEngineFlame.Update(myCurrentFlame, { myPosition.x - 48, myPosition.y - 9 });
		//printf_s("Player Direction X: %f Y: %f \n", myDirection.x, myDirection.y);
		
	}
	void Player::RapidFireLogic()
	{
		ActivateRapidFire();

		RapidFireIsActive();

		DeactivateRapidFire();

	}
	//Check if key is pressed and cooldown has expired
	void Player::ActivateRapidFire()
	{
		if (InputManager::GetInstance()->IsKeyPressed('1') && myRapidFireCurrentCooldown > myPlayerData->GetRapidFireMaxCooldown())
		{
			myRapidFireCurrentCooldown = 0.f;

			myRapidFireIsActive = true;
			if (myHasPurchasedPenetratingRounds)
			{
				myHasPenetratingRounds = true;
			}

			myPlayerData->SetShootCoolDown(myPlayerData->GetShootCoolDown() * (1 - myPlayerData->GetRapidFireAttackSpeed() * 0.01));
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
	void Player::DeactivateRapidFire()
	{
		if (myRapidFireCurrentlyActiveTime > myPlayerData->GetRapidFireMaxActiveTime())
		{
			myRapidFireIsActive = false;
			myHasPenetratingRounds = false;
			myPlayerData->SetShootCoolDown(myPlayerData->GetShootCoolDown() / (1 - myPlayerData->GetRapidFireAttackSpeed() * 0.01));
		}
	}
	void Player::AddAnotherProjectile()
	{
		if (myAmountOfProjectiles > 3)
		{
			myAmountOfProjectiles = 3;
		}
	}
}

