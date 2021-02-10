#include "stdafx.h"
#include "BulletFactory.h"
#include "TypePattern_Bullet.h"
#include "Bullet.h"
#include "Missile.h"
#include "AOEBullet.h"
#include "TimedBomb.h"
namespace Studio
{
	BulletFactory::~BulletFactory()
	{
		for (auto& it : myBullets)
		{
			SAFE_DELETE((it).second);
		}
	}

	void BulletFactory::InitBulletType(const std::string& aPath, const unsigned int aLayerOrder, const std::string& aType, float aSpeed, Enums::BulletOwner aOwner)
	{
		std::pair<std::string, TypePattern_Bullet*> temp_pair(aType, new TypePattern_Bullet(aPath, aLayerOrder, aSpeed, aOwner));
		myBullets.insert(temp_pair);
	}

	Bullet* BulletFactory::CreateBulletObject(const std::string& aType, const Tga2D::Vector2f& aPosition, const float aDamage)
	{
		auto tempObject = new Bullet(aPosition, myBullets.at(aType), aDamage);
		return tempObject;
	}

	Bullet* BulletFactory::CreateBulletObject(const std::string& aType, const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aDirection, const float aDamage)
	{
		auto tempObject = new Bullet(aPosition, aDirection, myBullets.at(aType), aDamage);
		return tempObject;
	}

	//Missile* BulletFactory::CreateMissileObject(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition)
	Missile* BulletFactory::CreateMissileObject(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aExplosionRadius)
	{
		auto missile = new Missile(aOwner, aPosition, aExplosionRadius);
		missile->SetOwner(aOwner);
		return missile;
	}


	AOEBullet* BulletFactory::CreateAOEBullet(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aRadius)
	{
		auto aoeBullet = new AOEBullet(aOwner, aPosition, aRadius);
		return aoeBullet;
	}
	TimedBomb* BulletFactory::CreateTimedBomb(const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aVelocity, const float aBlastRadius, const float aDamage)
	{
		return new TimedBomb(aPosition, aVelocity, aBlastRadius, aDamage);
	}
}
