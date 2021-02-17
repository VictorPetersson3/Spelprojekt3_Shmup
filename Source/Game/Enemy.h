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
	class TypePattern_Enemy;
	class TurretPipe;
	class Enemy : public GameObject
	{
	public:
		Enemy(TypePattern_Enemy* aEnemyType, const Tga2D::Vector2f& aSpawnPosition);
		~Enemy();

		void Update(float aDeltaTime);
		void TurretLogic();
		void Shoot(float aDeltaTime);
		void DeathLogic();
		const bool GetIsTerrain() const;
		const bool GetIsPopcorn() const;
		int GetScoreValue();

		VECTOR2F GetPosition();

		std::vector<Bullet*>& GetBullets();

	private:
		void UpdateBullets(float aDeltaTime);
		void AddColliders();
		void AnimationLogic();
	private:
		int myScoreValue;
		bool myHasDied = false;
		bool myMovingUp;
		bool myMovingIdle;
		bool myMovingDown;
		float myShootTimer;
		std::vector<Bullet*> myBullets;

		Studio::Enums::MovementPattern myMovementType;
		TurretPipe* myTurretPipe;
		Movement* myMovement;
		TypePattern_Enemy* myType;
	};
}


