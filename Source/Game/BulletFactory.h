#pragma once
#include <map>
#include "Enums.h"

namespace Studio
{
	class Bullet;
	class Missile;
	class AOEBullet;
	class TimedBomb;
	class TypePattern_Bullet;
	class BulletFactory
	{
	public:
		BulletFactory() = default;
		~BulletFactory();
		void InitBulletType(const std::string & aPath, const unsigned int aLayerOrder, const std::string & aType, float aSpeed, Enums::BulletOwner aBulletOwner);
		Bullet* CreateBulletObject(const std::string & aType, const Tga2D::Vector2f & aPosition, const float aDamage);
		Bullet* CreateBulletObject(const std::string& aType, const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aDirection, const float aDamage);
		//Missile* CreateMissileObject(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition);
		//Missile* CreateMissileObject(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aDirection);
		Missile* CreateMissileObject(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition,const float aExplosionRadius);
		AOEBullet* CreateAOEBullet(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aRadius);
		TimedBomb* CreateTimedBomb(const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aVelocity, const float aBlastRadius, const float aDamage);

	private:
		std::map<std::string, TypePattern_Bullet*> myBullets;
	};
}


