#include "stdafx.h"
#include "TypePattern_Background.h"
#include <tga2d/sprite/sprite.h>

Studio::TypePattern_Background::TypePattern_Background(const std::string& aPath, const unsigned int aLayerOrder) :
	myLayerOrder(aLayerOrder)
{
	mySprite = nullptr;
	mySprite = new Tga2D::CSprite(aPath.c_str());
	mySprite->SetPivot({0.5f, 0.5f});
}

Studio::TypePattern_Background::~TypePattern_Background()
{
	delete mySprite;
	mySprite = nullptr;
}

const unsigned int Studio::TypePattern_Background::GetLayerOrder() const
{
	return myLayerOrder;
}

Tga2D::CSprite* Studio::TypePattern_Background::GetSprite()
{
	return mySprite;
}
