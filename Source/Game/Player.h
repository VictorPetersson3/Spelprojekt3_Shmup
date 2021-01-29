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
	class RenderCommand;
	class Bullet;
	class EngineFlame;
	class Player : public GameObject
	{
	public:
		Player(const char* aImagePath);
		~Player();

		void Update();
		void Shoot();

	private:
		void Movement();

		void RapidFireLogic(float aCDReductionPercentage);
		void ActivateRapidFire(float aCDReductionPercentage);
		void RapidFireIsActive();
		void DeactivateRapidFire(float aCDReductionPercentage);
	private:
		float mySpeed;
		float myShootCooldown;
		float myTimeSinceLastShot;
		float myAnimationTurnSpeed;
		float myCurrentFlame;
		float myRapidFireMaxCooldown;
		float myRapidFireCurrentCooldown;
		float myRapidFireCurrentlyActiveTime;
		float myRapidFireMaxActiveTime;
		bool myIsAnimating = false;
		bool myIsAnimatingDown = false;
		bool myIsAnimatingUp = false;
		bool myIsRebounding = false;
		bool myRapidFireIsActive = false;

		VECTOR2F myPosition;
		VECTOR2F myFrames;
		EngineFlame myEngineFlame;
		
	};
}


