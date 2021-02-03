#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Renderer.h"
#include "RendererAccessor.h"
#include "tga2d/sprite/sprite.h"
#include "MovementStraight.h"
#include "MovementWave.h"
#include "MovementDiagonal.h"
#include "MovementBobbing.h"
#include "MovementSeeking.h"
#include "CoinAccessor.h"
#include "ScoreAccessor.h"
#include "LevelAccessor.h"
#include "Timer.h"
#include <string>
#include "TypePattern_Enemy.h"

namespace Studio
{
	Enemy::Enemy(TypePattern_Enemy* aEnemyType, const Tga2D::Vector2f& aSpawnPosition) :
		Enemy::GameObject(aEnemyType->GetImagePath())
	{
		myType = aEnemyType;
		GameObject::SetPosition(aSpawnPosition);
		myScoreValue = 100;
		myShootTimer = 0;
		SAFE_CREATE(myBulletSprite, Tga2D::CSprite("sprites/debugpixel.dds"));
		Enemy::GameObject::GetCollider().AddCircleColliderObject(myPosition, 50);
		switch (aEnemyType->GetMovementType())
		{
		case Studio::Enums::MovementPattern::Bobbing :
			SAFE_CREATE(myMovement, MovementBobbing(GameObject::GetPositionPointer(), myType->GetSpeed(), myType->GetBobbingHeigth()));
			break;
		case Studio::Enums::MovementPattern::Wave:
			SAFE_CREATE(myMovement, MovementWave(GameObject::GetPositionPointer(), myType->GetHorizontalSpeed()
				, myType->GetVerticalSpeed(), myType->GetWaveHeigth()));
			break;
		case Studio::Enums::MovementPattern::Straight:
			SAFE_CREATE(myMovement, MovementStraight(GameObject::GetPositionPointer(), myType->GetSpeed()));
			break;
		case Studio::Enums::MovementPattern::Seeking:
			SAFE_CREATE(myMovement, MovementSeeking(GameObject::GetPositionPointer(), Tga2D::Vector2f::Zero,
				myType->GetSpeed(), myType->GetAcceleration() ));
			break;
		case Studio::Enums::MovementPattern::Diagonal:
			if (myType->GetDiagonalIsTop())
			{
				Tga2D::Vector2f angle = GameObject::GetPosition() * -1;
				float theta = atan(GameObject::GetPosition().y / GameObject::GetPosition().x);
				SAFE_CREATE(myMovement, MovementDiagonal(GameObject::GetPositionPointer(),
					myType->GetSpeed(), angle));
			}
			else
			{
				Tga2D::Vector2f angle = Tga2D::Vector2f({0, 1080}) - GameObject::GetPosition();
				SAFE_CREATE(myMovement, MovementDiagonal(GameObject::GetPositionPointer(),
					myType->GetSpeed(), angle.GetNormalized()));
			}
			break;
		default:
			break;
		}
	}

	Enemy::~Enemy()
	{
		SAFE_DELETE(myBulletSprite);
		SAFE_DELETE(myMovement);
	}

	void Enemy::Update(float aDeltaTime)
	{
		if (!IsDead())
		{
			myMovement->Update();

			Shoot(aDeltaTime);

			Enemy::GameObject::Update(myPosition);
		}

		UpdateBullets(aDeltaTime);

		for (int i = 0; i < myBullets.size(); i++)
		{
			Studio::RendererAccessor::GetInstance()->Render(*myBullets[i]);
		}
	}

	void Enemy::Shoot(float aDeltaTime)
	{
		if (!myType->GetIsTerrain())
		{
			myShootTimer += aDeltaTime;
			if (myShootTimer > myType->GetShootInterval())
			{
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Enemy", myPosition);
				myShootTimer = 0;
			}
		}
	}

	const bool Enemy::GetIsTerrain()
	{
		return myType->GetIsTerrain();
	}
	void Enemy::DeathLogic()
	{
		if (!myHasDied)
		{
			CoinAccessor::GetInstance()->CreateCoin(myPosition);
			ScoreAccessor::GetInstance()->AddKillScore(1);
			printf_s("%f", myPosition.x);
			myHasDied = true;
		}
	}

	int Enemy::GetScoreValue()
	{
		return myScoreValue;
	}

	VECTOR2F Enemy::GetPosition()
	{
		return myPosition;
	}

	std::vector<Bullet*>& Enemy::GetBullets()
	{
		return myBullets;
	}

	void Enemy::UpdateBullets(float aDeltaTime)
	{
		for (int i = 0; i < myBullets.size(); i++)
		{
			myBullets[i]->Update();

			if (myBullets[i]->GetPosition().x > 1920 || myBullets[i]->GetPosition().x < 0 || myBullets[i]->GetPosition().y < 0 || myBullets[i]->GetPosition().y > 1080)
			{
				myBullets.erase(myBullets.begin() + i);
			}
		}
	}
}

