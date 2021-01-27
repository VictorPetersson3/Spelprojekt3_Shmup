#include "stdafx.h"
#include "BackgroundObject.h"
#include <tga2d/sprite/sprite.h>
#include "CommonUtilities/CURandom.h"
#include "TypePattern_Background.h"
//#include <iostream>
namespace Studio
{
	BackgroundObject::BackgroundObject(TypePattern_Background* aTypeObject, rapidjson::Value& aJsonObject) :
		GameObject::GameObject(aTypeObject->GetImagePath(), {aJsonObject["Scale"]["X"].GetFloat(), aJsonObject["Scale"]["Y"].GetFloat()}),
		myTypeObject(aTypeObject)
	{
		if (aJsonObject["UseRandom"].GetBool())
		{
			myPosition.x = CommonUtilities::GetRandomFloat(aJsonObject["RandomAtributes"]["RandomPositionXmin"].GetFloat(),
				aJsonObject["RandomAtributes"]["RandomPositionXmax"].GetFloat());
			myPosition.y = CommonUtilities::GetRandomFloat(aJsonObject["RandomAtributes"]["RandomPositionYmin"].GetFloat(),
				aJsonObject["RandomAtributes"]["RandomPositionYmax"].GetFloat());
			myScrollSpeed = CommonUtilities::GetRandomFloat(aJsonObject["RandomAtributes"]["RandomSpeed"]["Min"].GetFloat(),
				aJsonObject["RandomAtributes"]["RandomSpeed"]["Max"].GetFloat());
		}
		else
		{
			myPosition.x = aJsonObject["Position"]["X"].GetFloat();
			myPosition.y = aJsonObject["Position"]["Y"].GetFloat();
			myScrollSpeed = aJsonObject["Speed"].GetFloat();
		}
		myIsTiling = aJsonObject["IsTiling"].GetBool();
	}

	BackgroundObject::BackgroundObject(TypePattern_Background* aTypeObject, rapidjson::Value& aJsonObject, int aIndex) :
		GameObject::GameObject(aTypeObject->GetImagePath(), { aJsonObject["Scale"]["X"].GetFloat(), aJsonObject["Scale"]["Y"].GetFloat() }),
		myTypeObject(aTypeObject)
	{
		myPosition.x = aJsonObject["Position"]["X"].GetFloat() + (aIndex * GameObject::GetSpriteSheet().GetSprite()->GetImageSize().x);
		myPosition.y = aJsonObject["Position"]["Y"].GetFloat();
		myScrollSpeed = aJsonObject["Speed"].GetFloat();
		myIsTiling = aJsonObject["IsTiling"].GetBool();
	}
	
	BackgroundObject::~BackgroundObject()
	{
		GameObject::~GameObject();
	}
	void BackgroundObject::Update(float aDeltaTime)
	{
		myPosition.x = myPosition.x + myScrollSpeed * aDeltaTime;
		//std::cout << "Cloud XPosition" << myPosition.x << std::endl;
		GameObject::Update(myPosition);
	}
	const Tga2D::Vector2f& BackgroundObject::GetPosition() const
	{
		return myPosition;
	}
	void BackgroundObject::SetPosition(const Tga2D::Vector2f& aPosition)
	{
		myPosition = aPosition;
	}
	const bool BackgroundObject::GetIsTiling() const
	{
		return myIsTiling;
	}
	const TypePattern_Background* BackgroundObject::GetTypeObject() const
	{
		return myTypeObject;
	}
}