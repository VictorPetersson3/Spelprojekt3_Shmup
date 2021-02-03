#include "stdafx.h"
#include "Bullet.h"
#include "tga2d/sprite/sprite.h"
#include "TypePattern_Bullet.h"
#include "Timer.h"
namespace Studio
{
	Bullet::Bullet(VECTOR2F aPosition, TypePattern_Bullet* aTypePattern) :
		Bullet::GameObject(aTypePattern->GetImagePath()),
		myTypePattern(aTypePattern)
	{
		myPosition = aPosition;
		Bullet::GetSpriteSheet().SetSize({20.0f, 20.0f});
		Bullet::GameObject::GetCollider().AddCircleColliderObject(myPosition, 2.0f);
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Update()
	{
		myPosition.x += myTypePattern->GetSpeed() * Timer::GetInstance()->TGetDeltaTime();

		Bullet::GameObject::Update(myPosition);
	}

	void Bullet::RegisterEnemyHit(GameObject* anEnemy)
	{
		myHitEnemies.push_back(anEnemy);
	}

	void Bullet::SetIsPenetrating()
	{
		myIsPenetrating = true;
	}

	bool Bullet::GetIsPenetrating()
	{
		return myIsPenetrating;
	}

	bool Bullet::IsEnemyAlreadyHit(GameObject* anEnemy)
	{
		for (int i = 0; i < myHitEnemies.size(); i++)
		{
			if (myHitEnemies[i] == anEnemy) return true;
		}
		return false;
	}

	VECTOR2F Bullet::GetPosition()
	{
		return myPosition;
	}
	Enums::BulletOwner Bullet::GetOwner()
	{
		return myTypePattern->GetOwner();
	}
}

