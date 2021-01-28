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
	private:
		float mySpeed;
		float myShootCooldown;
		float myAnimationTurnSpeed;
		float myAnimationTime;
		float myCurrentFlame;
		bool myIsAnimating = false;
		bool myIsAnimatingDown = false;
		bool myIsAnimatingUp = false;
		bool myIsRebounding = false;

		VECTOR2F myPosition;
		VECTOR2F myFrames;
		EngineFlame myEngineFlame;
		
	};
}


