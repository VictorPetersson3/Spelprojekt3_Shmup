#include "stdafx.h"
#include "TypePattern_Background.h"
#include <tga2d/sprite/sprite.h>

Studio::TypePattern_Background::TypePattern_Background(rapidjson::Value& aJsonObject)
{
	myImagePath = aJsonObject["ImagePath"].GetString();
	if (aJsonObject["CreateMany"].GetBool())
	{
		myAmount = aJsonObject["Amount"].GetFloat();
	}
	else
	{
		myAmount = 1;
	}
}



const std::string& Studio::TypePattern_Background::GetImagePath() const
{
	return myImagePath;
}

const int Studio::TypePattern_Background::GetAmount() const
{
	return myAmount;
}
