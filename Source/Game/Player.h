#pragma once
#include "GameObject.h"
#include "EngineFlame.h"
#include "Enums.h"
#include <vector>
namespace Tga2D
{
	class CSprite;
}
namespace Studio
{
	class Player_JsonParser;
	class RenderCommand;
	class Bullet;
	class EngineFlame;
	class PowerUpModule;
	class Player : public GameObject
	{
	public:
		Player(Player_JsonParser* somePlayerData);
		~Player();

		void Update();
		void Shoot();
		void Bounce(const Tga2D::Vector2f aObjectPosition);
		const Tga2D::Vector2f GetDirection() const;
		const Tga2D::Vector2f GetNextFramePosition() const;
		const bool GetHasCollided() const;

		void UpgradeT1(Enums::Tier1Upgrades aTier1Upgrade);
		void UpgradeT2(Enums::Tier2Upgrades aTier2Upgrade);
		void UpgradeT3(Enums::Tier3Upgrades aTier3Upgrade);
		void ResetPlayerCurrentLevel();
		void TakeShieldDamage(int someDamage);
		void TakeDamage(const int someDamage);
		bool GetHasPenetratingRounds();
		bool GetIsShieldActive();
		bool GetHasClusterBombs();
		bool GetHasExplodingShield();
		float GetAmountOfProjectiles();

		Player_JsonParser* GetPlayerData();
	private:
		void Movement();
		void RapidFireLogic();
		void ActivateRapidFire();
		void RapidFireIsActive();
		void DeactivateRapidFire();
		void AddAnotherProjectile();
		void LaunchMissile();
		void ActivateInvincibility();
		void InvincibilityLogic();
		//Shield
		void ShieldLogic();
		void ActivateShield();
		void ShieldIsActive();
		void DeactivateShield();
	private:

		float mySpeed;
		float myTimeSinceLastShot;
		float myAnimationTurnSpeed;
		float myCurrentFlame;
		float myRapidFireCurrentCooldown;
		float myRapidFireCurrentlyActiveTime;
		float myRapidFireMaxActiveTime;
		float myInvincibilityTimer;

		//BasicAttacks
		float myAmountOfProjectiles;

		float myBounceBackTime;
		float myCurrentBounceTime;

		//Shield
		float myShieldCurrentActiveTime;
		float myShieldCurrentCooldown;
		int myShieldHealth;

		//Missile
		float myMissileCurrentCooldown;

		VECTOR2F myPosition;
		VECTOR2F myDirection;
		VECTOR2F myBounceDirection;

		bool myIsAnimating = false;
		bool myIsAnimatingDown = false;
		bool myIsAnimatingUp = false;
		bool myIsRebounding = false;
		bool myRapidFireIsActive = false;
		bool myHasCollided = false;
		bool myHasPenetratingRounds = false;
		bool myHasPurchasedPenetratingRounds = false;
		bool myHasPurchasedShieldExplosion = false;
		bool myHasPurchasedClusterBombs = false;
		bool myIsInvincible = false;

		//Shield
		bool myShieldIsActive = false;

		EngineFlame myEngineFlame;
		Player_JsonParser* myPlayerData;

		std::vector<PowerUpModule*> myPowerUpModules;
		PowerUpModule* myShieldModule;
	};
}


