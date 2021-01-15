#include "stdafx.h"
#include "TypePattern_Bullet.h"
#include "tga2d/sprite/sprite.h"

Studio::TypePattern_Bullet::TypePattern_Bullet(const std::string& aPath)
{
	std::shared_ptr<Tga2D::CSprite> sprite = std::make_shared<Tga2D::CSprite>(aPath.c_str());
	mySprite = sprite;
}

std::shared_ptr<Tga2D::CSprite> Studio::TypePattern_Bullet::GetSprite()
{
	return mySprite;
}
