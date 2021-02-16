#include "stdafx.h"
#include "Missile.h"
#include "TypePattern_Bullet.h"
#include "Timer.h"
#include "LevelAccessor.h"
#include "PlayerAccessor.h"
#include "AudioManager.h"
#include "AudioManagerAccesor.h"

#include "Renderer.h"
#include "RendererAccessor.h"
#include <tga2d/sprite/sprite.h>

namespace Studio
{
	Missile::Missile(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aExplosionRadius)
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
			myExplosionRadius = aExplosionRadius;
			myDamage = 0;

			myVelocity = { myInitialSpeed, 0.0f };

			myCollider.AddBoxColliderObject({ 0, 0 }, { 5,5 });

			if (PlayerAccessor::GetInstance()->GetHasClusterBombs())
			{
				mySpriteSheet.SetImagePath("sprites/bullets/missilelvl2.dds");
			}
			else
			{
				mySpriteSheet.SetImagePath("sprites/bullets/missilelvl1.dds");
			}
			myIsReversed = false;
		}
		if (aOwner == Enums::BulletOwner::Enemy)
		{
			myTypePattern = new TypePattern_Bullet("sprites/bullets/missilelvl1.dds", 12, 0.0f, aOwner);
			myPosition = aPosition;

			myIsSlowingDown = false;

			// TODO: Make JSON??
			myInitialSpeed = -10.0f;
			myDeaccelerationSpeed = -50.0f;
			myAccelerationSpeed = -2.0f;
			myExplosionRadius = aExplosionRadius;
			myDamage = 1;

			myVelocity = { myInitialSpeed, 0.0f };

			myCollider.AddBoxColliderObject({ 0, 0 }, { 10,5 });

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

		// Shake the camera # TEST
		RendererAccessor::GetInstance()->ShakeCamera(0.5f, 0.0625f);
	}

	void Missile::Impact()
	{
		LevelAccessor::GetInstance()->SpawnAOEBullet(myTypePattern->GetOwner(), myPosition, myExplosionRadius);

		AudioManagerAccessor::GetInstance()->Play2D("Audio/Explosion.mp3", false, 0.15f);

		// Shake the camera # TEST
		RendererAccessor::GetInstance()->ShakeCamera(15.0f, 0.25f);

		if (myTypePattern->GetOwner() == Enums::BulletOwner::Player
			&& PlayerAccessor::GetInstance()->GetHasClusterBombs()
			)
		{
			float angle = 180.0f / MATH_PI * 90.0f;
			for (float degree = 0.0f; degree < 6.0f; degree++)
			{
				float angle = (2.0f * MATH_PI) / 6.0f * degree;

				LevelAccessor::GetInstance()->SpawnTimedBomb(myPosition,
					{
						cos(angle) * 250.0f,
						sin(angle) * 250.0f
					},
					myExplosionRadius * 0.5f,
					myDamage * 0.5f);
			}
		}
	}
}
