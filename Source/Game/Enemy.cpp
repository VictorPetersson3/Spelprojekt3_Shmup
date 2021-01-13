#include "stdafx.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Renderer.h"
#include "tga2d/sprite/sprite.h"

namespace Studio
{
	Enemy::Enemy(Tga2D::CSprite* aSprite) :
		Enemy::GameObject(aSprite)
	{
		myPosition = { 1.0f, 0.5f };
		mySpeed = 0.05f;
		myShootCooldown = 0.0f;
		mySprite = aSprite;
		mySprite->SetSizeRelativeToImage({ 50, 50 });
		mySprite->SetPivot({ 0.5f, 0.5f });
		SAFE_CREATE(myBulletSprite, Tga2D::CSprite("sprites/debugpixel.dds"));
	}

	Enemy::~Enemy()
	{
		SAFE_DELETE(myBulletSprite);
		
	}

	void Enemy::Update(float aDeltaTime)
	{
		myPosition.x -= mySpeed * aDeltaTime;

		Shoot(aDeltaTime);

		Enemy::GameObject::Update(myPosition);

	}

	void Enemy::Shoot(float aDeltaTime)
	{
		myShootCooldown += aDeltaTime;
		if (myShootCooldown > 0.7f)
		{
			myBullets.push_back(new Bullet(myPosition, 1.0f, myBulletSprite));
			myShootCooldown = 0;
		}
	}

	std::vector<Bullet*>& Enemy::GetBullets()
	{
		return myBullets;
	}

	RenderCommand& Enemy::GetRenderCommand()
	{
		return Enemy::GameObject::GetRenderCommand();
	}
}

