#include "stdafx.h"
#include "BulletFactory.h"
#include "Bullet.h"

Studio::BulletFactory::~BulletFactory()
{
	for (auto it = myBulletObjects.begin(); it != myBulletObjects.end(); ++it)
	{
		delete (*it).second;
		SAFE_DELETE((*it).second);
	}
}

void Studio::BulletFactory::InitBulletType(const std::string& aPath, const unsigned int aLayerOrder, const std::string& aType)
{
	std::pair<std::string, Studio::TypePattern_Bullet*> temp_pair(aType, new Studio::TypePattern_Bullet(aPath, aLayerOrder));
	myBulletObjects.insert(temp_pair);
}

Studio::Bullet* Studio::BulletFactory::CreateBulletObject(const std::string& aType, const Tga2D::Vector2f& aPosition, const float& aSpeed)
{
	Studio::Bullet* tempObject = new Studio::Bullet(aPosition, aSpeed, myBulletObjects.at(aType)->GetSprite());
	return tempObject;
}



