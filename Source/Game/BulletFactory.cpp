#include "stdafx.h"
#include "BulletFactory.h"
#include "TypePattern_Bullet.h"
#include "Bullet.h"
#include "Missile.h"
#include "AOEBullet.h"
namespace Studio
{
	BulletFactory::~BulletFactory()
	{
		for (auto it = myBullets.begin(); it != myBullets.end(); ++it)
		{
			delete (*it).second;
			SAFE_DELETE((*it).second);
		}
	}

	void BulletFactory::InitBulletType(const std::string& aPath, const unsigned int aLayerOrder, const std::string& aType, float aSpeed, Enums::BulletOwner aOwner)
	{
		std::pair<std::string, TypePattern_Bullet*> temp_pair(aType, new TypePattern_Bullet(aPath, aLayerOrder, aSpeed, aOwner));
		myBullets.insert(temp_pair);
	}

	Bullet* BulletFactory::CreateBulletObject(const std::string& aType, const Tga2D::Vector2f& aPosition)
	{
		auto tempObject = new Bullet(aPosition, myBullets.at(aType));
		return tempObject;
	}

	Missile* BulletFactory::CreateMissileObject(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition)
	{
		auto missile = new Missile(aOwner, aPosition);
		missile->SetOwner(aOwner);
		return missile;
	}

	AOEBullet* BulletFactory::CreateAOEBullet(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aRadius)
	{
		auto aoeBullet = new AOEBullet(aOwner, aPosition, aRadius);
		return aoeBullet;
	}
}
