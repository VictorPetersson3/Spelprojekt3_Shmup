#pragma once
#include "Bullet.h"
#include "Counter.h"
namespace Studio
{
	class TimedBomb : public Bullet
	{
	public:
		TimedBomb(const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aVelocity, const float aBlastRadius, const float aDamage);
		void Update() override;

	private:
		float myBlastRadius;
		Counter myCounter;
		VECTOR2F myVelocity;
	};
}
