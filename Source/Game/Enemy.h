#pragma once
#include "GameObject.h"
#include <vector>
#include "Enums.h"

namespace Tga2D
{
	class CSprite;
}
namespace Studio
{
	class RenderCommand;
	class Bullet;
	class Movement; 
	enum class MovementType;
	class Enemy : public GameObject
	{
	public:
		Enemy(Tga2D::CSprite* aSprite, VECTOR2F aSpawnPosition);
		~Enemy();

		void Update(float aDeltaTime);
		void Shoot(float aDeltaTime);
		void PlayExplosion();
		
		bool HasFinishedExplosion();

		int GetScoreValue();

		VECTOR2F GetPosition();

		std::vector<Bullet*>& GetBullets();

		Studio::RenderCommand& GetRenderCommand();


	private:
		void UpdateBullets(float aDeltaTime);
	private:
		int myScoreValue;

		bool myHasDied = false;

		float mySpeed;
		float myShootCooldown;

		std::vector<Bullet*> myBullets;

		Tga2D::CSprite* mySprite;
		Tga2D::CSprite* myBulletSprite;

		Studio::Enums::MovementPattern aMovementType;

		Movement* myMovement;


		VECTOR2F myPosition;

	};
}


