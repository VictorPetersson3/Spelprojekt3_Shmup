#include "stdafx.h"
#include "Bullet.h"
#include "tga2d/sprite/sprite.h"
#include "TypePattern_Bullet.h"
#include "Timer.h"
#include "PlayerAccessor.h"
namespace Studio
{
	Bullet::Bullet()
	{
	}
	Bullet::Bullet(VECTOR2F aPosition, TypePattern_Bullet* aTypePattern, const float aDamage) :
		Bullet::GameObject(aTypePattern->GetImagePath()),
		myTypePattern(aTypePattern)
	{
		myPosition = aPosition;
		//Bullet::GetSpriteSheet().SetSize({20.0f, 20.0f});
		Bullet::GameObject::GetCollider().AddCircleColliderObject({0, 0}, 2.0f);
		myHasDirection = false;

		myDamage = aDamage;

		if (myTypePattern->GetOwner() == Enums::BulletOwner::Player && PlayerAccessor::GetInstance()->GetHasPenetratingRounds())
		{
			mySpriteSheet.SetImagePath("Sprites/Bullets/BlueBullet.dds");
		}
	}

	Bullet::Bullet(const VECTOR2F& aPosition, const VECTOR2F& aDirection, TypePattern_Bullet* aTypePattern, const float aDamage):
		Bullet::GameObject(aTypePattern->GetImagePath()),
		myTypePattern(aTypePattern)
	{
		myPosition = aPosition;
		//Bullet::GetSpriteSheet().SetSize({ 10.0f, 10.0f });
		Bullet::GameObject::GetCollider().AddCircleColliderObject({ 0, 0 }, 2.0f);
		myDirection = aDirection;
		myHasDirection = true;

		myDamage = aDamage;
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Update()
	{
		if (myHasDirection)
		{
			myPosition = myPosition + (myDirection * myTypePattern->GetSpeed() * Timer::GetInstance()->TGetDeltaTime());
			//printf("Turret Bullet Position X: %f Y: %f\n", myPosition.x, myPosition.y);
		}
		else
		{
			myPosition.x += myTypePattern->GetSpeed() * Timer::GetInstance()->TGetDeltaTime();
		}

		Bullet::GameObject::Update(myPosition);
	}

	// Overrideable by Missile etc
	void Bullet::Impact() {}

	void Bullet::RegisterEnemyHit(GameObject* anEnemy)
	{
		myHitEnemies.push_back(anEnemy);
	}

	void Bullet::SetIsPenetrating()
	{
		myIsPenetrating = true;
	}

	float Bullet::GetDamage()
	{
		return myDamage;
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
	void Bullet::SetOwner(const Enums::BulletOwner& aNewOwner)
	{
		myTypePattern->SetOwner(aNewOwner);
	}
	const bool Bullet::ShouldDeleteThis() const
	{
		return myDeleteMeThisFrame;
	}
	void Bullet::ShouldDeleteThis(const bool aDeleteIt)
	{
		myDeleteMeThisFrame = aDeleteIt;
	}
	Enums::BulletOwner Bullet::GetOwner() const
	{
		return myTypePattern->GetOwner();
	}
}

