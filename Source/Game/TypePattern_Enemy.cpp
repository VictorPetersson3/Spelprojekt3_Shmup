#include "stdafx.h"
#include "TypePattern_Enemy.h"
#include "tga2d/sprite/sprite.h"

TypePattern_Enemy::TypePattern_Enemy(const std::string& aPath)
{
	std::shared_ptr<Tga2D::CSprite> sprite = std::make_shared<Tga2D::CSprite>(aPath.c_str());
	mySprite = sprite;
}

std::shared_ptr<Tga2D::CSprite> TypePattern_Enemy::GetSprite()
{
	return mySprite;
}
