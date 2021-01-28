#pragma once
#include "GameObject.h"
#include "Particle_SpriteSheet_Factory.h"
#include "ParticleObject.h"
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
		void PlayExplosion();

		bool IsFinishedExploding();

		std::vector<Bullet*>& GetBullets();

		RenderCommand& GetRenderCommand();
	private:
		void Movement();
		void UpdateBullets();
	private:
		float mySpeed;
		float myShootCooldown;
		float myAnimationTurnSpeed;
		float myCurrentFlame;
		bool myHasDied = false;
		bool myIsAnimating = false;
		bool myIsAnimatingDown = false;
		bool myIsAnimatingUp = false;
		bool myIsRebounding = false;

		std::vector<Bullet*> myBullets;
		std::vector<ParticleObject*> myParticleObjects;

		Tga2D::CSprite* myBulletSprite;
		VECTOR2F myPosition;
		VECTOR2F myFrames;
		EngineFlame myEngineFlame;
		Particle_SpriteSheet_Factory myParticleFactory;
		
	};
}


