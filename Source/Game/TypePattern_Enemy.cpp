#include "stdafx.h"
#include "TypePattern_Enemy.h"
#include "tga2d/sprite/sprite.h"

Studio::TypePattern_Enemy::TypePattern_Enemy(const std::string& aPath, const unsigned int aLayerOrder) :
	myLayerOrder(aLayerOrder)
{
	mySprite = nullptr;
	mySprite = new Tga2D::CSprite(aPath.c_str());
	mySprite->SetPivot({ 0.5f, 0.5f });
}

Studio::TypePattern_Enemy::~TypePattern_Enemy()
{
	delete mySprite;
	mySprite = nullptr;
}

const unsigned int Studio::TypePattern_Enemy::GetLayerOrder() const
{
	return myLayerOrder;
}

Tga2D::CSprite* Studio::TypePattern_Enemy::GetSprite()
{
	return mySprite;
}
