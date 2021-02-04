#include "stdafx.h"
#include "AOEBullet.h"
#include "TypePattern_Bullet.h"
namespace Studio
{
	AOEBullet::AOEBullet(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, float aRadius)
	{
		myTypePattern = new TypePattern_Bullet("Sprites/Particles/AOE_Temp.dds", 12, 0.0f, aOwner);
		myPosition = aPosition;

		myCollider.AddCircleColliderObject({ 0, 0 }, aRadius);
		mySpriteSheet.SetSize({ aRadius * 2, aRadius * 2 });

		mySpriteSheet.SetImagePath("Sprites/Particles/AOE_Temp.dds");
		myIsPenetrating = true;

		// Arbitrary explosion time (hitbox)
		myCounter.SetInterval(0.1f);
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
