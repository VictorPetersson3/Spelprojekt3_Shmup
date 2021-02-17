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

#define PI (3.14159265358979323846f)
#define EPSILON (0.001f)
#define SPRITESHEET GameObject::GetSpriteSheet()

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
		myPosition.x += 200;
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
			if (!myType->GetIsUpright())
			{
				mySpriteSheet.SetSizeRelativeToImage({1, -1});
			}
		}
		if (aEnemyType->GetIsPopcorn())
		{
			SPRITESHEET.SetAmountOfFrames({ 4, 1 });
			SPRITESHEET.LoopAnimationInRange(0.083f, { 1,1 }, {3,1});
		}
		if (!aEnemyType->GetIsPopcorn() && !aEnemyType->GetIsTurret() && !aEnemyType->GetIsTerrain() && aEnemyType->GetIsAnimating())
		{
			SPRITESHEET.SetAmountOfFrames(aEnemyType->GetAmountOfFrames());
		}
	}

	Enemy::~Enemy()
	{
		AudioManagerAccessor::GetInstance()->Play2D("Audio/EnemyKilled.flac", false, 0.4f);

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
			AnimationLogic();
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
	void Enemy::AnimationLogic()
	{
		if (!myType->GetIsPopcorn() && !myType->GetIsTurret() && !myType->GetIsTerrain() && myType->GetIsAnimating())
		{
			float angle = atan(myMovement->GetDirection().y / myMovement->GetDirection().x);
			if (myMovementType == Studio::Enums::MovementPattern::Wave)
			{
				if (angle > 0 - EPSILON && angle < 0 + EPSILON && !myMovingIdle)
				{
					myMovingUp = false;
					myMovingDown = false;
					//SPRITESHEET.ReverseAndStartAnimation();
					if (!SPRITESHEET.IsAnimating())
					{
						SPRITESHEET.LoopAnimationInRange(0.083f, myType->GetIdleAnimationRange().first, myType->GetIdleAnimationRange().second);
						myMovingIdle = true;
					}
				}
				if (angle > 0 + EPSILON && !myMovingUp && myMovingDown || myMovingIdle)
				{
					myMovingUp = true;
					myMovingDown = false;
					myMovingIdle = false;
					SPRITESHEET.PlayAnimationInRange(0.083f, myType->GetUpAnimationRange().first, myType->GetUpAnimationRange().second);
				}
				if (angle < 0 - EPSILON && !myMovingDown && myMovingUp || myMovingIdle)
				{
					myMovingUp = false;
					myMovingDown = true;
					myMovingIdle = false;
					SPRITESHEET.PlayAnimationInRange(0.083f, myType->GetDownAnimationRange().first, myType->GetDownAnimationRange().second);
				}
			}
			else
			{
				if (!SPRITESHEET.IsAnimating())
				{
					SPRITESHEET.LoopAnimationInRange(0.083f, myType->GetIdleAnimationRange().first, myType->GetIdleAnimationRange().second);
					myMovingIdle = true;
				}
			}

		}
	}
}

