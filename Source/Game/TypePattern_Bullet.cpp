#include "stdafx.h"
#include "TypePattern_Bullet.h"
#include "tga2d/sprite/sprite.h"

Studio::TypePattern_Bullet::TypePattern_Bullet(const std::string& aPath, const unsigned int aLayerOrder, const float aSpeed, const Studio::Enums::BulletOwner aOwner) :
	myLayerOrder(aLayerOrder),
	myImagePath(aPath),
	mySpeed(aSpeed),
	myOwner(aOwner)
{
}

Studio::TypePattern_Bullet::~TypePattern_Bullet()
{
}

const unsigned int Studio::TypePattern_Bullet::GetLayerOrder() const
{
	return myLayerOrder;
}

const std::string& Studio::TypePattern_Bullet::GetImagePath()
{
	return myImagePath;
}

const float Studio::TypePattern_Bullet::GetSpeed()
{
	return mySpeed;
}

const Studio::Enums::BulletOwner Studio::TypePattern_Bullet::GetOwner()
{
	return myOwner;
}

void Studio::TypePattern_Bullet::SetOwner(const Enums::BulletOwner& aNewOwner)
{
	myOwner = aNewOwner;
}

