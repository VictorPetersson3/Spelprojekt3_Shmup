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
		Enemy(Tga2D::CSprite* aSprite, VECTOR2F aSpawnPosition);
		~Enemy();

		void Update(float aDeltaTime);
		void Shoot(float aDeltaTime);

		int GetScoreValue();

		VECTOR2F GetPosition();

		std::vector<Bullet*>& GetBullets();

		Studio::RenderCommand& GetRenderCommand();

	private:
		void UpdateBullets(float aDeltaTime);
	private:
		int myScoreValue;

		float mySpeed;
		float myShootCooldown;

		std::vector<Bullet*> myBullets;

		Tga2D::CSprite* mySprite;
		Tga2D::CSprite* myBulletSprite;
		VECTOR2F myPosition;

	};
}


