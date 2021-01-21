#pragma once
#include "GameObject.h"
#include "Particle_SpriteSheet_Factory.h"
#include "ParticleObject.h"
#include <vector>
namespace Tga2D
{
	class CSprite;
}
namespace Studio
{
	class RenderCommand;
	class Bullet;
	class Player : public GameObject
	{
	public:
		Player(Tga2D::CSprite* aSprite);
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
		bool myHasDied = false;
		std::vector<Bullet*> myBullets;
		std::vector<ParticleObject*> myParticleObjects;

		Tga2D::CSprite* mySprite;
		Tga2D::CSprite* myBulletSprite;
		VECTOR2F myPosition;

		Particle_SpriteSheet_Factory myParticleFactory;
		
	};
}


