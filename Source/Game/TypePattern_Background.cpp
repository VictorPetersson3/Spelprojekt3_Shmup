#include "stdafx.h"
#include "TypePattern_Background.h"
#include <tga2d/sprite/sprite.h>

Studio::TypePattern_Background::TypePattern_Background(rapidjson::Value& aJsonObject)
{
	mySprite = nullptr;
	mySprite = new Tga2D::CSprite(aJsonObject["ImagePath"].GetString());
	if (aJsonObject["IsCentered"].IsTrue())
	{
		mySprite->SetPivot({ 0.5f, 0.5f });
	}
	else
	{
		mySprite->SetPivot({aJsonObject["Pivot"]["X"].GetFloat(), aJsonObject["Pivot"]["Y"].GetFloat() });
	}
}

Studio::TypePattern_Background::~TypePattern_Background()
{
	delete mySprite;
	mySprite = nullptr;
}

Tga2D::CSprite* Studio::TypePattern_Background::GetSprite()
{
	return mySprite;
}
