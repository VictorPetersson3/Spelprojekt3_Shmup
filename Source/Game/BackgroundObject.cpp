#include "stdafx.h"
#include "BackgroundObject.h"
#include <tga2d/sprite/sprite.h>
//#include <iostream>
namespace Studio
{
	BackgroundObject::BackgroundObject(Tga2D::CSprite* aSprite, const Tga2D::Vector2f& aPosition, float aSpeed) :
		GameObject::GameObject(aSprite),
		mySprite(aSprite)
	{
		myPosition = aPosition;
		myScrollSpeed = aSpeed;
	}

	BackgroundObject::BackgroundObject(Tga2D::CSprite* aSprite, const Tga2D::Vector2f& aPosition, float aSpeed, const Tga2D::Vector2f& aSize) :
		GameObject::GameObject(aSprite, aSize),
		mySprite(aSprite)
	{
		myPosition = aPosition;
		myScrollSpeed = aSpeed;
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
}