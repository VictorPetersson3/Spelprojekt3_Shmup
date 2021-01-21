#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Renderer.h"
#include "RendererAccessor.h"
#include "tga2d/sprite/sprite.h"
#include "MovementStraight.h"
#include "MovementWave.h"

namespace Studio
{
	Enemy::Enemy(Tga2D::CSprite* aSprite, VECTOR2F aSpawnPosition) :
		Enemy::GameObject(aSprite)
	{
		myPosition = aSpawnPosition;
		mySpeed = 300;
		myShootCooldown = 0.0f;
		myScoreValue = 100;
		mySprite = aSprite;
		mySprite->SetSizeRelativeToImage({ 50, 50 });
		mySprite->SetPivot({ 0.5f, 0.5f });
		SAFE_CREATE(myBulletSprite, Tga2D::CSprite("sprites/debugpixel.dds"));
		SAFE_CREATE(myMovement, MovementWave(&myPosition, 100.0f, 500.0f, 500.0f));

		Enemy::GameObject::GetCollider().AddCircleColliderObject(myPosition, 25);
	}

	Enemy::~Enemy()
	{
		SAFE_DELETE(myBulletSprite);
		SAFE_DELETE(myMovement);
	}

	void Enemy::Update(float aDeltaTime)
	{
		myMovement->Update();

		Shoot(aDeltaTime);

		UpdateBullets(aDeltaTime);

		Enemy::GameObject::Update(myPosition);

		for (int i = 0; i < myBullets.size(); i++)
		{
			Studio::RendererAccessor::GetInstance()->Render(*myBullets[i]);
		}

	}

	void Enemy::Shoot(float aDeltaTime)
	{
		myShootCooldown += aDeltaTime;
		if (myShootCooldown > 0.7f)
		{
			myBullets.push_back(new Bullet(myPosition, -500, myBulletSprite));
			myShootCooldown = 0;
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

	RenderCommand& Enemy::GetRenderCommand()
	{
		return Enemy::GameObject::GetRenderCommand();
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

