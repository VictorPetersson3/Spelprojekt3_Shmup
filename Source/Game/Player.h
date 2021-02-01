#pragma once
#include "GameObject.h"
#include "EngineFlame.h"
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
	class Player : public GameObject
	{
	public:
		Player(Player_JsonParser* somePlayerData);
		~Player();

		void Update();
		void Shoot();
		void Bounce(const Tga2D::Vector2f aObjectPosition);
		const Tga2D::Vector2f GetDirection() const;
		const bool GetHasCollided() const;

	private:
		void Movement();
		void RapidFireLogic(float aCDReductionPercentage);
		void ActivateRapidFire(float aCDReductionPercentage);
		void RapidFireIsActive();
		void DeactivateRapidFire(float aCDReductionPercentage);


	private:
		float mySpeed;
		float myTimeSinceLastShot;
		float myAnimationTurnSpeed;
		float myCurrentFlame;
		float myRapidFireCurrentCooldown;
		float myRapidFireCurrentlyActiveTime;
		float myRapidFireMaxActiveTime;

		float myBounceBackTime;
		float myCurrentBounceTime;

		VECTOR2F myPosition;
		VECTOR2F myDirection;
		VECTOR2F myBounceDirection;

		bool myIsAnimating = false;
		bool myIsAnimatingDown = false;
		bool myIsAnimatingUp = false;
		bool myIsRebounding = false;
		bool myRapidFireIsActive = false;
		bool myHasCollided = false;

		EngineFlame myEngineFlame;
		Player_JsonParser* myPlayerData;
	};
}


