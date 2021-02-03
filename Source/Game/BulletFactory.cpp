#include "stdafx.h"
#include "BulletFactory.h"
#include "TypePattern_Bullet.h"
#include "Bullet.h"
#include "Missile.h"

Studio::BulletFactory::~BulletFactory()
{
	for (auto it = myBullets.begin(); it != myBullets.end(); ++it)
	{
		delete (*it).second;
		SAFE_DELETE((*it).second);
	}
}

void Studio::BulletFactory::InitBulletType(const std::string& aPath, const unsigned int aLayerOrder, const std::string& aType, float aSpeed, Enums::BulletOwner aOwner)
{
	std::pair<std::string, Studio::TypePattern_Bullet*> temp_pair(aType, new Studio::TypePattern_Bullet(aPath, aLayerOrder, aSpeed, aOwner));
	myBullets.insert(temp_pair);
}

Studio::Bullet* Studio::BulletFactory::CreateBulletObject(const std::string& aType, const Tga2D::Vector2f& aPosition)
{
	Studio::Bullet* tempObject = new Studio::Bullet(aPosition, myBullets.at(aType));
	return tempObject;
}

Studio::Missile* Studio::BulletFactory::CreateMissileObject(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition)
{
	Studio::Missile* missile = new Studio::Missile(aOwner, aPosition);
	missile->SetOwner(aOwner);
	return missile;
}
