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
	class Player : public GameObject
	{
	public:
		Player(Tga2D::CSprite* aSprite);
		~Player();

		void Update(float aDeltaTime);
		void Shoot(float aDeltaTime);

		std::vector<Bullet*>& GetBullets();

		RenderCommand& GetRenderCommand();
	private:
		void Movement(float aDeltaTime);
		void UpdateBullets(float aDeltaTime);
	private:
		float mySpeed;
		float myShootCooldown;
		std::vector<Bullet*> myBullets;

		Tga2D::CSprite* mySprite;
		Tga2D::CSprite* myBulletSprite;
		VECTOR2F myPosition;

	};
}


