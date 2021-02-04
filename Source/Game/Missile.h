#pragma once
#include "Bullet.h"
namespace Studio
{
	class Missile : public Bullet
	{
	public:
		Missile(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition);
		Missile::Missile(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, float aDirection);
		void Update() override;
		void Impact() override;

	private:

		float myInitialSpeed,
			myDeaccelerationSpeed,
			myAccelerationSpeed;
		bool myIsSlowingDown;
		bool myIsReversed;

		Tga2D::Vector2f myVelocity;
	};
}