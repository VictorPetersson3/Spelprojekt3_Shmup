#include "stdafx.h"
#include "TypePattern_Background.h"
#include <tga2d/sprite/sprite.h>

Studio::TypePattern_Background::TypePattern_Background(rapidjson::Value& aJsonObject)
{
	myImagePath = aJsonObject["ImagePath"].GetString();
	if (aJsonObject["IsCentered"].IsTrue())
	{
		mySpritePivot = { 0.5f, 0.5f };
	}
	else
	{
		mySpritePivot = {aJsonObject["Pivot"]["X"].GetFloat(), aJsonObject["Pivot"]["Y"].GetFloat() };
	}
}

const Tga2D::Vector2f& Studio::TypePattern_Background::GetImagePivot() const
{
	return mySpritePivot;
}



const std::string& Studio::TypePattern_Background::GetImagePath() const
{
	return myImagePath;
}
