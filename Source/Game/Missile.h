#pragma once
#include "Bullet.h"
namespace Studio
{
	class Missile : public Bullet
	{
	public:
		Missile(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition);
		void Update() override;
		void Impact() override;

	private:

		float myInitialSpeed,
			myDeaccelerationSpeed,
			myAccelerationSpeed;
		bool myIsSlowingDown;

		Tga2D::Vector2f myVelocity;
	};
}