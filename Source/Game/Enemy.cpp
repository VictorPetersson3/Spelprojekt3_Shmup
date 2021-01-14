#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Renderer.h"
#include "tga2d/sprite/sprite.h"

namespace Studio
{
	Enemy::Enemy(Tga2D::CSprite* aSprite, VECTOR2F aSpawnPosition) :
		Enemy::GameObject(aSprite)
	{
		myPosition = aSpawnPosition;
		mySpeed = 0.05f;
		myShootCooldown = 0.0f;
		mySprite = aSprite;
		mySprite->SetSizeRelativeToImage({ 50, 50 });
		mySprite->SetPivot({ 0.5f, 0.5f });
		SAFE_CREATE(myBulletSprite, Tga2D::CSprite("sprites/debugpixel.dds"));

		Enemy::GameObject::GetCollider().AddCircleColliderObject(myPosition, 0.03f);
	}

	Enemy::~Enemy()
	{
		SAFE_DELETE(myBulletSprite);
		
	}

	void Enemy::Update(float aDeltaTime)
	{
		myPosition.x -= mySpeed * aDeltaTime;

		Shoot(aDeltaTime);

		UpdateBullets(aDeltaTime);

		Enemy::GameObject::Update(myPosition);

	}

	void Enemy::Shoot(float aDeltaTime)
	{
		myShootCooldown += aDeltaTime;
		if (myShootCooldown > 0.7f)
		{
			myBullets.push_back(new Bullet(myPosition, -0.2f, myBulletSprite));
			myShootCooldown = 0;
		}
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
			myBullets[i]->Update(aDeltaTime);

			if (myBullets[i]->GetPosition().x > 1.0f || myBullets[i]->GetPosition().x < 0.0f || myBullets[i]->GetPosition().y < 0.0f || myBullets[i]->GetPosition().y > 1.0f)
			{
				myBullets.erase(myBullets.begin() + i);
			}
		}
	}
}

