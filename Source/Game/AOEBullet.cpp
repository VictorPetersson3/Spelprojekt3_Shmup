#include "stdafx.h"
#include "AOEBullet.h"
#include "TypePattern_Bullet.h"
#include "PlayerAccessor.h"
#include "Player_JsonParser.h"
#include "LevelAccessor.h"
namespace Studio
{
	AOEBullet::AOEBullet(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, float aRadius)
	{
		printf_s("\n[AOE]\nCreated by %s at {%f, %f} with radius: %f\n\n",
			aOwner == Enums::BulletOwner::Player ? "Player" : "Boss",
			aPosition.x, aPosition.y,
			aRadius
		);

		myTypePattern = new TypePattern_Bullet("Sprites/Particles/AOE_Temp.dds", 12, 0.0f, aOwner);
		myPosition = aPosition;

		myCollider.AddCircleColliderObject({ 0, 0 }, aRadius);
		//mySpriteSheet.SetSize({ aRadius * 2, aRadius * 2 });
		mySpriteSheet.SetSize({ 0.0f, 0.0f });

		mySpriteSheet.SetImagePath("Sprites/Particles/AOE_Temp.dds");
		myIsPenetrating = true;

		// Arbitrary explosion time (hitbox)
		myCounter.SetInterval(0.1f);

		if (aOwner == Enums::BulletOwner::Player)
		{
			myDamage = PlayerAccessor::GetInstance()->GetPlayerData()->GetMissileDamage();
		}
		else
		{
			myDamage = 1;
		}

		LevelAccessor::GetInstance()->CreateExplosionAt(myPosition, aRadius);
	}

	void AOEBullet::Update()
	{
		myCounter.Tick();
		if (myCounter.PastInterval())
		{
			myDeleteMeThisFrame = true;
		}

		GameObject::Update(myPosition);
	}

	void AOEBullet::Impact() {}
}
