#pragma once
#include "Bullet.h"
#include "Counter.h"
namespace Studio
{
	class AOEBullet : public Bullet
	{
	public:
		AOEBullet(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, float aRadius);
		void Update() override;
		void Impact() override;

	private:
		Counter myCounter;
	};
}

