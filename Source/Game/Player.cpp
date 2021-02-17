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
#include "PowerUpModule.h"
#include "AudioManagerAccesor.h"
#include "AudioManager.h"
#include "MenuManagerSingleton.h"


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
		myShieldCurrentActiveTime = 0.f;
		myShieldCurrentCooldown = 0.f;
		myShieldHealth = somePlayerData->GetShieldHealth();
		myAmountOfProjectiles = 1;
		myInvincibilityTimer = 0.f;

		myMissileCurrentCooldown = 0.f;

		mySpeed = somePlayerData->GetMinSpeed();
		myRapidFireMaxActiveTime = somePlayerData->GetRapidFireMaxActiveTime();
		myRapidFireCurrentCooldown = 0.f;
		GetCollider().AddCircleColliderObject({0,0}, 20);

		myPowerUpModules.push_back(new PowerUpModule(Enums::PowerUpModules::Shield));
		myShieldModule = myPowerUpModules[0]; 
	}

	Player::~Player()
	{
		for (PowerUpModule* module : myPowerUpModules)
		{
			SAFE_DELETE(module);
		}
		myPowerUpModules.clear();
	}

	void Player::Update()
	{
		if (!IsDead() && !MenuManagerSingleton::GetInstance()->GetShop()->GetIsEnabled())
		{
			Movement();

			Player::GameObject::Update(myPosition + myDirection);

			for (PowerUpModule* module : myPowerUpModules)
			{
				if (module->GetIsShield())
				{
					if (myShieldIsActive)
						module->Update();
				}	
				else
					module->Update();
			}

			InvincibilityLogic();

			Shoot();

			RapidFireLogic();

			ShieldLogic();

			MenuManagerSingleton::GetInstance()->GreyOutAbilitiesOnCooldown(myRapidFireCurrentCooldown, myMissileCurrentCooldown, myShieldCurrentCooldown);

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
		if (InputManager::GetInstance()->IsCustomKeyDown(Enums::CustomKeys::CustomKey_Shoot) && myTimeSinceLastShot > myPlayerData->GetShootCoolDown())
		{

			AudioManagerAccessor::GetInstance()->Play2D("Audio/BasicAttack.mp3", false, 0.2f);

			if (myAmountOfProjectiles == 1)
			{
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y - 5.f }, 1);

			}
			else if (myAmountOfProjectiles == 2)
			{
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y - 20.f }, 1);
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y + 10.f }, 1);

			}
			else if (myAmountOfProjectiles == 3)
			{
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y - 5.f }, 1);
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y - 30.f }, 1);
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Player", { myPosition.x, myPosition.y + 20.f }, 1);
			}
			myTimeSinceLastShot = 0.f;

			// Launch
			// TODO: Don't do this all the time

		}
		myMissileCurrentCooldown -= Timer::GetInstance()->TGetDeltaTime();
		if (InputManager::GetInstance()->IsCustomKeyPressed(Enums::CustomKeys::CustomKey_Explosive) && myMissileCurrentCooldown <= 0)
		{
			LaunchMissile();
			myMissileCurrentCooldown = myPlayerData->GetMissileCooldown();
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

	const Tga2D::Vector2f Studio::Player::GetNextFramePosition() const
	{
		return myPosition + myDirection.GetNormalized() * mySpeed * Timer::GetInstance()->TGetDeltaTime();
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
		case Studio::Enums::Tier1Upgrades::BasicAttackSpeed:
			myPlayerData->UpgradeBasicAttackSpeedT1();
			break;
		case Studio::Enums::Tier1Upgrades::MissileExplosionRadius:
			myPlayerData->UpgradeMissileRadiusT1();
			break;
		case Studio::Enums::Tier1Upgrades::MissileCooldown:
			myPlayerData->UpgradeMissileCooldownT1();
			break;
		case Studio::Enums::Tier1Upgrades::MissileDamage:
			myPlayerData->UpgradeMissileDamageT1();
			break;
		case Studio::Enums::Tier1Upgrades::ShieldDuration:
			myPlayerData->UpgradeShieldDurationT1();
			break;
		case Studio::Enums::Tier1Upgrades::ShieldHealth:
			myPlayerData->UpgradeShieldHealthT1();
			break;
		case Studio::Enums::Tier1Upgrades::ShieldCooldown:
			myPlayerData->UpgradeShieldCooldownT1();
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
			if (myAmountOfProjectiles == 1)
				myPowerUpModules.push_back(new PowerUpModule(Enums::PowerUpModules::BasicAttackFirst));
			else if (myAmountOfProjectiles == 2)
				myPowerUpModules.push_back(new PowerUpModule(Enums::PowerUpModules::BasicAttackSecond));

			AddAnotherProjectile();
			break;
		case Studio::Enums::Tier2Upgrades::MissileExplosionRadius:
			myPlayerData->UpgradeMissileRadiusT2();
			break;
		case Studio::Enums::Tier2Upgrades::MissileCooldown:
			myPlayerData->UpgradeMissileCooldownT2();
			break;
		case Studio::Enums::Tier2Upgrades::MissileDamage:
			myPlayerData->UpgradeMissileDamageT2();
			break;
		case Studio::Enums::Tier2Upgrades::ShieldDuration:
			myPlayerData->UpgradeShieldDurationT2();
			break;
		case Studio::Enums::Tier2Upgrades::ShieldHealth:
			myPlayerData->UpgradeShieldHealthT2();
			break;
		case Studio::Enums::Tier2Upgrades::ShieldCooldown:
			myPlayerData->UpgradeShieldCooldownT2();
			break;
		}
	}

	void Player::UpgradeT3(Enums::Tier3Upgrades aTier3Upgrade)
	{
		switch (aTier3Upgrade)
		{
		case Studio::Enums::Tier3Upgrades::RapidFirePenetrating:
			myHasPurchasedPenetratingRounds = true;
			myPowerUpModules.push_back(new PowerUpModule(Enums::PowerUpModules::RapidFire));
			break;
		case Studio::Enums::Tier3Upgrades::BasicAttackSpeed:
			myPlayerData->UpgradeBasicAttackSpeedT3();
			break;
		case Studio::Enums::Tier3Upgrades::MissileCluster:
			break;
		case Studio::Enums::Tier3Upgrades::ShieldExplosion:
			myShieldModule->GetSpriteSheet().SetImagePath("Sprites/assets/player/upgrades/effects/shieldSpriteRed.dds");
			myShieldModule->GetSpriteSheet().SetSize({ 512.f,512.f });
			myShieldModule->GetSpriteSheet().SetAmountOfFrames({ 4,4 });
			myHasPurchasedShieldExplosion = true;
			break;
		}
	}

	void Studio::Player::ResetPlayerCurrentLevel()
	{
		myShieldCurrentCooldown = 0.f;
		myMissileCurrentCooldown = 0.f;
		myRapidFireCurrentCooldown = 0.f;
		GameObject::GetHealth().ResetHealth();
		myPosition = { 300, 540 };
		GameObject::SetPosition(myPosition);
		
	}

	bool Player::GetHasPenetratingRounds()
	{
		return myHasPenetratingRounds;
	}

	const bool Player::GetHasCollided() const
	{
		return myHasCollided;
	}

	float Studio::Player::GetAmountOfProjectiles()
	{
		if (this != nullptr)
		{
			return myAmountOfProjectiles;
		}
	}

	void Player::Movement()
	{

		bool wKey = InputManager::GetInstance()->IsCustomKeyDown(Enums::CustomKeys::CustomKey_FlyUp);
		bool aKey = InputManager::GetInstance()->IsCustomKeyDown(Enums::CustomKeys::CustomKey_FlyLeft);
		bool sKey = InputManager::GetInstance()->IsCustomKeyDown(Enums::CustomKeys::CustomKey_FlyDown);
		bool dKey = InputManager::GetInstance()->IsCustomKeyDown(Enums::CustomKeys::CustomKey_FlyRight);
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
			//printf("Player Speed: %f\n", mySpeed);
			if (wKey && myPosition.y > 30)
			{
				if (myIsAnimatingDown || !myIsAnimating)
				{
					myIsAnimatingDown = false;
					SPRITESHEET.PlayAnimationInRange(myPlayerData->GetAnimationTurnSpeed(), myPlayerData->GetDownAnimationRange().first, myPlayerData->GetDownAnimationRange().second);

					for (PowerUpModule* module : myPowerUpModules)
					{
						if (!module->GetIsShield())
							module->GetSpriteSheet().PlayAnimationInRange(myPlayerData->GetAnimationTurnSpeed(), myPlayerData->GetDownAnimationRange().first, myPlayerData->GetDownAnimationRange().second);
					}
					myIsAnimatingUp = true;
					myIsAnimating = true;
				}
				myDirection.y -= mySpeed * Timer::GetInstance()->TGetDeltaTime();
			}
			//A
			if (aKey && myPosition.x > 300)
			{
				myDirection.x -= mySpeed * Timer::GetInstance()->TGetDeltaTime();
				myCurrentFlame = 1;
			}
			//S
			if (sKey && myPosition.y < 1050)
			{
				if (myIsAnimatingUp || !myIsAnimating)
				{
					myIsAnimatingUp = false;
					SPRITESHEET.PlayAnimationInRange(myPlayerData->GetAnimationTurnSpeed(), myPlayerData->GetUpAnimationRange().first, myPlayerData->GetUpAnimationRange().second);

					for (PowerUpModule* module : myPowerUpModules)
					{
						if (!module->GetIsShield())
							module->GetSpriteSheet().PlayAnimationInRange(myPlayerData->GetAnimationTurnSpeed(), myPlayerData->GetUpAnimationRange().first, myPlayerData->GetUpAnimationRange().second);
					}
					myIsAnimatingDown = true;
					myIsAnimating = true;
				}

				myDirection.y += mySpeed * Timer::GetInstance()->TGetDeltaTime();
			}
			//D
			if (dKey && myPosition.x < 1820)
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
							for (PowerUpModule* module : myPowerUpModules)
							{
								if (!module->GetIsShield())
									module->GetSpriteSheet().ReverseAndStartAnimation();
							}
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
							for (PowerUpModule* module : myPowerUpModules)
							{
								if (!module->GetIsShield())
									module->GetSpriteSheet().ReverseAndStartAnimation();
							}
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
					for (PowerUpModule* module : myPowerUpModules)
					{
						if (!module->GetIsShield())
							module->SetFrame({1, 1});
					}
				}
			}
			if (!aKey && !dKey)
			{
				myCurrentFlame = 2;
			}
			//Spacebar
		}
		myPosition += myDirection.Normalize() * mySpeed * Timer::GetInstance()->TGetDeltaTime();
		myEngineFlame.Update(myCurrentFlame, { myPosition.x - 48, myPosition.y });
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
		if (InputManager::GetInstance()->IsCustomKeyPressed(Enums::CustomKeys::CustomKey_RapidFire) && myRapidFireCurrentCooldown <= 0)
		{
			myRapidFireCurrentCooldown = myPlayerData->GetRapidFireMaxCooldown() + myPlayerData->GetRapidFireMaxActiveTime();
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
		}
		myRapidFireCurrentCooldown -= Timer::GetInstance()->TGetDeltaTime();

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
		myAmountOfProjectiles++;
		if (myAmountOfProjectiles > 3)
		{
			myAmountOfProjectiles = 3;
		}
	}

	void Player::LaunchMissile()
	{
		Studio::LevelAccessor::GetInstance()->SpawnMissile(Enums::BulletOwner::Player, myPosition, myPlayerData->GetMissileRadius(), myPlayerData->GetMissileDamage(), myPlayerData->GetMissileDamage());
	}
	
	
	void Studio::Player::ShieldLogic()
	{
		if (InputManager::GetInstance()->IsCustomKeyPressed(Enums::CustomKey_Shield) && myShieldCurrentCooldown <= 0)
		{
			ActivateShield();
		}
		if (myShieldIsActive)
		{
			ShieldIsActive();
		}
		if (myShieldHealth <= 0 || myShieldCurrentActiveTime > myPlayerData->GetShieldDuration())
		{
			DeactivateShield();
		}
		myShieldCurrentCooldown -= Timer::GetInstance()->TGetDeltaTime();

	}
	void Studio::Player::ActivateShield()
	{
		for (PowerUpModule* module : myPowerUpModules)
		{
			if (module->GetIsShield())
			{
				module->GetSpriteSheet().PlayAnimationInRange(0.1f, { 1,2 }, { 3,2 });
			}
		}
		myShieldHealth = myPlayerData->GetShieldHealth();
		myShieldIsActive = true;
		myShieldCurrentCooldown = myPlayerData->GetShieldCooldown() + myPlayerData->GetShieldDuration();
		AudioManagerAccessor::GetInstance()->Play2D("Audio/Shield.mp3", false, 0.5f);
	}
	void Studio::Player::ShieldIsActive()
	{
		if (!myShieldModule->GetSpriteSheet().IsAnimating())
		{
			myShieldModule->GetSpriteSheet().LoopAnimationInRange(0.1f, { 1,1 }, { 4,1 });
		}
		myShieldCurrentActiveTime += Timer::GetInstance()->TGetDeltaTime();
	}
	void Studio::Player::DeactivateShield()
	{
		myShieldIsActive = false;
		myShieldCurrentActiveTime = 0.f;
		myShieldHealth = myPlayerData->GetShieldHealth();
		if (myHasPurchasedShieldExplosion)
		{
			LevelAccessor::GetInstance()->SpawnAOEBullet(Enums::BulletOwner::Player, myPosition, 300.0f);
		}
		
	}
	void Studio::Player::ActivateInvincibility()
	{
		myInvincibilityTimer = 0.5f;
	}
	void Studio::Player::InvincibilityLogic()
	{
		
		myInvincibilityTimer -= Timer::GetInstance()->TGetDeltaTime();
		
		if (myInvincibilityTimer > 0.f)
		{
			myIsInvincible = true;
		}
		else
		{
			myIsInvincible = false;
		}
	}
	void Studio::Player::TakeShieldDamage(int someDamage)
	{
		if (!myIsInvincible)
		{
			myShieldHealth -= someDamage;
			ActivateInvincibility();
		}
	}
	void Studio::Player::TakeDamage(const int someDamage)
	{
		if (!myIsInvincible)
		{
			GameObject::TakeDamage(someDamage);
			ActivateInvincibility();
		}
	}
	bool Studio::Player::GetIsShieldActive()
	{
		return myShieldIsActive;
	}
	bool Studio::Player::GetHasClusterBombs()
	{
		return myHasPurchasedClusterBombs;
	}
	bool Studio::Player::GetHasExplodingShield()
	{
		return myHasPurchasedShieldExplosion;
	}
	Player_JsonParser* Studio::Player::GetPlayerData()
	{
		return myPlayerData;
	}
}
