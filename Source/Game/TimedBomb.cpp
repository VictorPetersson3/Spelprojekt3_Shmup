#include "stdafx.h"
#include "TimedBomb.h"
#include "Timer.h"
#include "TypePattern_Bullet.h"
#include "LevelAccessor.h"
#include "AudioManagerAccesor.h"
namespace Studio
{
	TimedBomb::TimedBomb(const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aVelocity, const float aBlastRadius, const float aDamage)
		: myBlastRadius(aBlastRadius), myVelocity(aVelocity)
	{
		myTypePattern = new TypePattern_Bullet("sprites/bullets/clusterBomb.dds", 12, 0.0f, Enums::BulletOwner::Player);
		myPosition = aPosition;
		myDamage = aDamage;
		mySpriteSheet.SetImagePath("sprites/bullets/clusterBomb.dds");
		mySpriteSheet.SetSize({ 16.f, 16.f });
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
			AudioManagerAccessor::GetInstance()->Play2D("Audio/Explosion.mp3", false, 0.025f);

		}

		GameObject::Update(myPosition);
	}
}
