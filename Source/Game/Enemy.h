#pragma once
#include "GameObject.h"
#include <vector>
namespace Tga2D
{
	class CSprite;
}
namespace Studio
{
	class RenderCommand;
	class Bullet;
	class Enemy : public GameObject
	{
	public:
		Enemy(Tga2D::CSprite* aSprite);
		~Enemy();

		void Update(float aDeltaTime);
		void Shoot(float aDeltaTime);

		std::vector<Bullet*>& GetBullets();

		Studio::RenderCommand& GetRenderCommand();
	private:
		float mySpeed;
		float myShootCooldown;
		std::vector<Bullet*> myBullets;

		Tga2D::CSprite* mySprite;
		Tga2D::CSprite* myBulletSprite;
		VECTOR2F myPosition;

	};
}


