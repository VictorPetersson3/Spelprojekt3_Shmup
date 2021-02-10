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
#include "TurretPipe.h"
#include "AudioManager.h"
#include "AudioManagerAccesor.h"

namespace Studio
{
	Enemy::Enemy(TypePattern_Enemy* aEnemyType, const Tga2D::Vector2f& aSpawnPosition) :
		Enemy::GameObject(aEnemyType->GetImagePath()),
		myMovementType(aEnemyType->GetMovementType())
	{
		myTurretPipe = nullptr;
		myMovement = nullptr;
		myType = aEnemyType;
		myPosition = aSpawnPosition;
		myScoreValue = 100;
		myShootTimer = 0;
		AddColliders();
		switch (aEnemyType->GetMovementType())
		{
		case Studio::Enums::MovementPattern::Bobbing :
			SAFE_CREATE(myMovement, MovementBobbing(&myPosition, myType->GetSpeed(), myType->GetBobbingHeigth()));
			break;
		case Studio::Enums::MovementPattern::Wave:
			SAFE_CREATE(myMovement, MovementWave(&myPosition, myType->GetHorizontalSpeed()
				, myType->GetVerticalSpeed(), myType->GetWaveHeigth()));
			break;
		case Studio::Enums::MovementPattern::Straight:
			SAFE_CREATE(myMovement, MovementStraight(&myPosition, myType->GetSpeed()));
			break;
		case Studio::Enums::MovementPattern::Seeking:
			SAFE_CREATE(myMovement, MovementSeeking(&myPosition, Tga2D::Vector2f::Zero,
				myType->GetSpeed(), myType->GetAcceleration() ));
			break;
		case Studio::Enums::MovementPattern::Diagonal:
			if (myType->GetDiagonalIsTop())
			{
				Tga2D::Vector2f angle = Tga2D::Vector2f({0, 1080}) - GameObject::GetPosition();
				SAFE_CREATE(myMovement, MovementDiagonal(&myPosition,
					myType->GetSpeed(), angle.GetNormalized()));
			}
			else
			{
				Tga2D::Vector2f angle = Tga2D::Vector2f({0, 0}) - GameObject::GetPosition();
				SAFE_CREATE(myMovement, MovementDiagonal(&myPosition,
					myType->GetSpeed(), angle.GetNormalized()));
			}
			break;
		default:
			break;
		}
		if (aEnemyType->GetIsTurret())
		{
			myTurretPipe = new TurretPipe(this, aEnemyType);
		}
		if (aEnemyType->GetIsPopcorn())
		{
			GameObject::GetSpriteSheet().SetAmountOfFrames({ 4, 1 });
			GameObject::GetSpriteSheet().LoopAnimationInRange(0.083f, { 1,1 }, {3,1});
		}
	}

	Enemy::~Enemy()
	{
		AudioManagerAccessor::GetInstance()->Play2D("Audio/Explosion.mp3", false, 0.2f);

		SAFE_DELETE(myMovement);
	}

	void Enemy::Update(float aDeltaTime)
	{
		if (!IsDead())
		{
			if (myType->GetIsTurret())
			{
				TurretLogic();
			}
			else
			{
				Shoot(aDeltaTime);
			}
			myMovement->Update();
			Enemy::GameObject::Update(myPosition);
		}

		UpdateBullets(aDeltaTime);

		for (int i = 0; i < myBullets.size(); i++)
		{
			Studio::RendererAccessor::GetInstance()->Render(*myBullets[i]);
		}
	}

	void Enemy::TurretLogic()
	{
		myTurretPipe->Update();
	}

	void Enemy::Shoot(float aDeltaTime)
	{
		if (!myType->GetIsTerrain() && !myType->GetIsPopcorn())
		{
			myShootTimer += aDeltaTime;
			if (myShootTimer > myType->GetShootInterval())
			{
				AudioManagerAccessor::GetInstance()->Play2D("Audio/EnemyBasicAttack.mp3", false, 0.05f);
				
				Studio::LevelAccessor::GetInstance()->SpawnBullet("Enemy", myPosition, 1);
				myShootTimer = 0;
			}
		}
	}

	const bool Enemy::GetIsTerrain() const
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

	const bool Enemy::GetIsPopcorn() const
	{
		return myType->GetIsPopcorn();
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
	void Enemy::AddColliders()
	{
		if (myType->GetHasExtraCollission())
		{
			for (int i = 0; i < myType->GetCircleColliders().size(); i++)
			{
				Enemy::GameObject::GetCollider().AddCircleColliderObject(myType->GetCircleColliders().at(i).second, myType->GetCircleColliders().at(i).first);
			}
			for (int i = 0; i < myType->GetBoxColliders().size(); i++)
			{
				Enemy::GameObject::GetCollider().AddBoxColliderObject(myType->GetBoxColliders().at(i).first, myType->GetBoxColliders().at(i).second);
			}
		}
		else
		{
			Enemy::GameObject::GetCollider().AddCircleColliderObject({0, 0}, 50);
		}
	}
}

