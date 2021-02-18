#include "stdafx.h"
#include "BackgroundObject.h"
#include <tga2d/sprite/sprite.h>
#include "CommonUtilities/CURandom.h"
#include "TypePattern_Background.h"
//#include <iostream>
namespace Studio
{
	BackgroundObject::BackgroundObject(TypePattern_Background* aTypeObject, rapidjson::Value& aJsonObject) :
		GameObject::GameObject(aTypeObject->GetImagePath()),
		myTypeObject(aTypeObject)
	{
		if (aJsonObject["UseRandom"].GetBool())
		{
			GameObject::SetPositionX(CommonUtilities::GetRandomFloat(aJsonObject["RandomAtributes"]["RandomPositionX"]["Min"].GetFloat(),
				aJsonObject["RandomAtributes"]["RandomPositionX"]["Max"].GetFloat()));
			GameObject::SetPositionY(CommonUtilities::GetRandomFloat(aJsonObject["RandomAtributes"]["RandomPositionY"]["Min"].GetFloat(),
				aJsonObject["RandomAtributes"]["RandomPositionY"]["Max"].GetFloat()));
			myScrollSpeed = CommonUtilities::GetRandomFloat(aJsonObject["RandomAtributes"]["RandomSpeed"]["Min"].GetFloat(),
				aJsonObject["RandomAtributes"]["RandomSpeed"]["Max"].GetFloat());
		}
		else
		{
			GameObject::SetPosition({ aJsonObject["Position"]["X"].GetFloat(), aJsonObject["Position"]["Y"].GetFloat() });
			GameObject::GetSpriteSheet().SetLayer(aJsonObject["LayerOrder"].GetFloat());
			myScrollSpeed = aJsonObject["Speed"].GetFloat();
		}
		GameObject::GetSpriteSheet().SetSizeRelativeToImage({ aJsonObject["Scale"]["X"].GetFloat(), aJsonObject["Scale"]["Y"].GetFloat()});
		myIsTiling = aJsonObject["IsTiling"].GetBool();
		if (aJsonObject["IsCentered"].IsTrue())
		{
			GameObject::GetSpriteSheet().SetPivot({ 0.5f, 0.5f });
		}
		else
		{
			GameObject::GetSpriteSheet().SetPivot({ aJsonObject["Pivot"]["X"].GetFloat(), aJsonObject["Pivot"]["Y"].GetFloat() });
		}

	}

	BackgroundObject::BackgroundObject(TypePattern_Background* aTypeObject, rapidjson::Value& aJsonObject, int aIndex) :
		GameObject::GameObject(aTypeObject->GetImagePath()),
		myTypeObject(aTypeObject)
	{
		GameObject::GetSpriteSheet().SetLayer(aJsonObject["LayerOrder"].GetFloat());
		myScrollSpeed = aJsonObject["Speed"].GetFloat();
		myIsTiling = aJsonObject["IsTiling"].GetBool();
		if (aJsonObject["IsCentered"].IsTrue())
		{
			GameObject::GetSpriteSheet().SetPivot({ 0.5f, 0.5f });
		}
		else
		{
			GameObject::GetSpriteSheet().SetPivot({ aJsonObject["Pivot"]["X"].GetFloat(), aJsonObject["Pivot"]["Y"].GetFloat() });
		}
		if (aJsonObject["UseRandom"].GetBool())
		{
			GameObject::SetPositionX(CommonUtilities::GetRandomFloat(aJsonObject["RandomAtributes"]["RandomPositionX"]["Min"].GetFloat(),
				aJsonObject["RandomAtributes"]["RandomPositionX"]["Max"].GetFloat()));
			GameObject::SetPositionY(CommonUtilities::GetRandomFloat(aJsonObject["RandomAtributes"]["RandomPositionY"]["Min"].GetFloat(),
				aJsonObject["RandomAtributes"]["RandomPositionY"]["Max"].GetFloat()));
			myScrollSpeed = CommonUtilities::GetRandomFloat(aJsonObject["RandomAtributes"]["RandomSpeed"]["Min"].GetFloat(),
				aJsonObject["RandomAtributes"]["RandomSpeed"]["Max"].GetFloat());
		}
		else
		{
			GameObject::SetPosition({ aJsonObject["Position"]["X"].GetFloat() + (aIndex * GameObject::GetSpriteSheet().GetSprite()->GetImageSize().x), aJsonObject["Position"]["Y"].GetFloat() });
			GameObject::GetSpriteSheet().SetLayer(aJsonObject["LayerOrder"].GetFloat());
			myScrollSpeed = aJsonObject["Speed"].GetFloat();
		}
		
		GameObject::GetSpriteSheet().SetSizeRelativeToImage({ aJsonObject["Scale"]["X"].GetFloat(), aJsonObject["Scale"]["Y"].GetFloat()});
	}
	
	BackgroundObject::~BackgroundObject()
	{
		GameObject::~GameObject();
	}
	void BackgroundObject::Update(float aDeltaTime)
	{
		GameObject::SetPositionX(GameObject::GetPosition().x + myScrollSpeed * aDeltaTime);
		//std::cout << "Cloud XPosition" << myPosition.x << std::endl;
		GameObject::Update(myPosition);
	}
	const Tga2D::Vector2f& BackgroundObject::GetPosition() const
	{
		return myPosition;
	}
	void BackgroundObject::SetPosition(const Tga2D::Vector2f& aPosition)
	{
		GameObject::SetPosition(aPosition);
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