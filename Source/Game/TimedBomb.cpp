#include "stdafx.h"
#include "TimedBomb.h"
#include "Timer.h"
#include "TypePattern_Bullet.h"
#include "LevelAccessor.h"
namespace Studio
{
	TimedBomb::TimedBomb(const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aVelocity, const float aBlastRadius, const float aDamage)
		: myBlastRadius(aBlastRadius), myVelocity(aVelocity)
	{
		myTypePattern = new TypePattern_Bullet("sprites/bullets/missilelvl1.dds", 12, 0.0f, Enums::BulletOwner::Player);
		myPosition = aPosition;
		myDamage = aDamage;
		mySpriteSheet.SetImagePath("sprites/bullets/missilelvl1.dds");
		myCounter.SetInterval(1.0f);
		myIsPenetrating = false;
		myCollider.AddCircleColliderObject(myPosition, 500.0f);
	}

	void TimedBomb::Update()
	{
		myPosition += myVelocity * DELTA_TIME;
		myVelocity -= myVelocity * 2.0f * DELTA_TIME;

		myCounter.Tick();
		if (myCounter.PastInterval())
		{
			myDeleteMeThisFrame = true;
			LevelAccessor::GetInstance()->SpawnAOEBullet(Enums::BulletOwner::Player, myPosition, myBlastRadius);
		}

		GameObject::Update(myPosition);
	}
}
