#include "stdafx.h"
#include "Missile.h"
#include "TypePattern_Bullet.h"
#include "Timer.h"
#include "LevelAccessor.h"
#include "tga2d/sprite/sprite.h"
namespace Studio
{
	Missile::Missile(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition)
	{
		if (aOwner == Enums::BulletOwner::Player)
		{
			myTypePattern = new TypePattern_Bullet("sprites/bullets/missilelvl1.dds", 12, 0.0f, aOwner);
			myPosition = aPosition;

			myIsSlowingDown = true;

			// TODO: Make JSON??
			myInitialSpeed = 400.0f;
			myDeaccelerationSpeed = 500.0f;
			myAccelerationSpeed = 100.0f;

			myVelocity = { myInitialSpeed, 0.0f };

			myCollider.AddBoxColliderObject({ 0, 0 }, { 5,5 });

			mySpriteSheet.SetImagePath("sprites/bullets/missilelvl1.dds");
			myIsReversed = false;
		}
		if (aOwner == Enums::BulletOwner::Enemy)
		{
			myTypePattern = new TypePattern_Bullet("sprites/bullets/missilelvl1.dds", 12, 0.0f, aOwner);
			myPosition = aPosition;

			myIsSlowingDown = true;

			// TODO: Make JSON??
			myInitialSpeed = -40.0f;
			myDeaccelerationSpeed = -50.0f;
			myAccelerationSpeed = -2.0f;

			myVelocity = { myInitialSpeed, 0.0f };

			myCollider.AddBoxColliderObject({ 0, 0 }, { 5,5 });

			mySpriteSheet.SetImagePath("sprites/bullets/missilelvl1.dds");

			mySpriteSheet.GetSprite()->SetTextureRect(1.0f, 0.0f, 0.0f, 1.0f);

			myIsReversed = true;
		}
	}

	void Missile::Update()
	{
		auto deltaTime = Timer::GetInstance()->TGetDeltaTime();

		if (!myIsReversed)
		{
			if (myIsSlowingDown)
			{
				myVelocity.x -= myDeaccelerationSpeed * deltaTime;

				if (myVelocity.x <= 0.0f)
				{
					myIsSlowingDown = false;
					myVelocity.x = 0.0f;
					myVelocity.y = 0.0f;
				}
			}
			else
			{
				myVelocity.x += myAccelerationSpeed;
			}
		}
		else
		{
			if (myIsSlowingDown)
			{
				myVelocity.x -= myDeaccelerationSpeed * deltaTime;

				if (myVelocity.x >= 0.0f)
				{
					myIsSlowingDown = false;
					myVelocity.x = 0.0f;
					myVelocity.y = 0.0f;
				}
			}
			else
			{
				myVelocity.x += myAccelerationSpeed;
			}
		}

		myPosition += myVelocity * deltaTime;
		GameObject::Update(myPosition);
	}

	void Missile::Impact()
	{
		printf_s("Missile impacted!\n");
		LevelAccessor::GetInstance()->SpawnAOEBullet(myTypePattern->GetOwner(), myPosition, 250.0f);
	}
}
