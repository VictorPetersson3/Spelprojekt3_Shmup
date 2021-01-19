#include "stdafx.h"
#include "CollisionObject.h"

Studio::CollisionObject::CollisionObject()
{
	myColliderType = ColliderType::NoCollider;
}

Studio::CollisionObject::CollisionObject(Tga2D::Vector2f aPosition, float aRadius)
{
	myColliderType = ColliderType::CircleCollider;
	myRadius = aRadius;
	myPosition = aPosition;
}

Studio::CollisionObject::CollisionObject(Tga2D::Vector2f aPosition, Tga2D::Vector2f aColliderSize)
{
	myColliderType = ColliderType::BoxCollider;
	myWidth = aColliderSize.x;
	myHeight = aColliderSize.y * (16.0f / 9.0f);
	myPosition = aPosition;
}

void Studio::CollisionObject::Update(const Tga2D::Vector2f& aPosition)
{
	myPosition = aPosition;
}

float const Studio::CollisionObject::GetWidth()
{
	return myWidth;
}

float const Studio::CollisionObject::GetHeight()
{
	return myHeight;
}

float const Studio::CollisionObject::GetRadius()
{
	return myRadius;
}

Studio::ColliderType& Studio::CollisionObject::GetColliderType()
{
	return myColliderType;
}

Tga2D::Vector2f Studio::CollisionObject::GetPosition()
{
	return myPosition;
}
