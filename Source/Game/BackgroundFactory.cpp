#include "stdafx.h"
#include "BackgroundFactory.h"
#include "BackgroundObject.h"


Studio::BackgroundFactory::~BackgroundFactory()
{
	for (auto it = myBackgroundObjects.begin(); it != myBackgroundObjects.end(); ++it)
	{
		delete (*it).second;
		SAFE_DELETE((*it).second);
	}
}

void Studio::BackgroundFactory::InitBackGroundObject(const std::string& aPath, const unsigned int aLayerOrder, const std::string& aType)
{
	std::pair<std::string, Studio::TypePattern_Background*> temp_pair(aType, new Studio::TypePattern_Background(aPath, aLayerOrder));
	myBackgroundObjects.insert(temp_pair);
}

Studio::BackgroundObject* Studio::BackgroundFactory::CreateBackgroundObject(const std::string& aType, const Tga2D::Vector2f& aPosition, float aSpeed)
{
	Studio::BackgroundObject* tempObject = new Studio::BackgroundObject(myBackgroundObjects.at(aType)->GetSprite(), aPosition, aSpeed);
	return tempObject;
}

Studio::BackgroundObject* Studio::BackgroundFactory::CreateBackgroundObject(const std::string& aType, const Tga2D::Vector2f& aPosition, float aSpeed, const Tga2D::Vector2f& aSize)
{
	Studio::BackgroundObject* tempObject = new Studio::BackgroundObject(myBackgroundObjects.at(aType)->GetSprite(), aPosition, aSpeed, aSize);
	return tempObject;
}
