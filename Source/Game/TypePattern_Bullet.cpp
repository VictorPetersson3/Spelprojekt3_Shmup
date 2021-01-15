#include "stdafx.h"
#include "TypePattern_Bullet.h"
#include "tga2d/sprite/sprite.h"

Studio::TypePattern_Bullet::TypePattern_Bullet(const std::string& aPath, const unsigned int aLayerOrder) :
	myLayerOrder(aLayerOrder)
{
	mySprite = nullptr;
	mySprite = new Tga2D::CSprite(aPath.c_str());
	mySprite->SetPivot({ 0.5f, 0.5f });
}

Studio::TypePattern_Bullet::~TypePattern_Bullet()
{
	delete mySprite;
	mySprite = nullptr;
}

const unsigned int Studio::TypePattern_Bullet::GetLayerOrder() const
{
	return myLayerOrder;
}

Tga2D::CSprite* Studio::TypePattern_Bullet::GetSprite()
{
	return mySprite;
}
