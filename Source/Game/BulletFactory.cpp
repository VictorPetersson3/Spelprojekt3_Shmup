#include "stdafx.h"
#include "BulletFactory.h"
#include "TypePattern_Bullet.h"
#include "Bullet.h"

Studio::BulletFactory::~BulletFactory()
{
	for (auto it = myBullets.begin(); it != myBullets.end(); ++it)
	{
		delete (*it).second;
		SAFE_DELETE((*it).second);
	}
}

void Studio::BulletFactory::InitBulletType(const std::string& aPath, const unsigned int aLayerOrder, const std::string& aType)
{
	std::pair<std::string, Studio::TypePattern_Bullet*> temp_pair(aType, new Studio::TypePattern_Bullet(aPath, aLayerOrder));
	myBullets.insert(temp_pair);
}

Studio::Bullet* Studio::BulletFactory::CreateBulletObject(const std::string& aType, float aSpeed, const Tga2D::Vector2f& aPosition)
{
	Studio::Bullet* tempObject = new Studio::Bullet(aPosition, aSpeed, myBullets.at(aType)->GetSprite());
	return tempObject;
}