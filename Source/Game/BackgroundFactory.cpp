#include "stdafx.h"
#include "BackgroundFactory.h"
#include "BackgroundObject.h"


void Studio::BackgroundFactory::InitBackGroundObject(rapidjson::Value& aJsonObject, const std::string& aType)
{
	std::pair<std::string, Studio::TypePattern_Background*> temp_pair(aType, new Studio::TypePattern_Background(aJsonObject));
	myBackgroundObjects.insert(temp_pair);
}

Studio::BackgroundObject* Studio::BackgroundFactory::CreateBackgroundObject(const std::string& aType, rapidjson::Value& aJsonObject)
{
	Studio::BackgroundObject* tempObject = new Studio::BackgroundObject(myBackgroundObjects.at(aType), aJsonObject);
	return tempObject;
}

Studio::BackgroundObject* Studio::BackgroundFactory::CreateBackgroundObject(const std::string& aType, rapidjson::Value& aJsonObject, int aIndex)
{
	Studio::BackgroundObject* tempObject = new Studio::BackgroundObject(myBackgroundObjects.at(aType), aJsonObject, aIndex);
	return tempObject;
}


