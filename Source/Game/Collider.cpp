#include "stdafx.h"
#include "Collider.h"
namespace Studio
{
	void Collider::AddColliderObject(CollisionObject& aCollisionObject)
	{
		myCollisionObjects.push_back(aCollisionObject);
	}

	bool Collider::Intersects(Collider& aCollider)
	{
		for (int i = 0; i < myCollisionObjects.size(); i++)
		{
			for (int j = 0; j < aCollider.myCollisionObjects.size(); j++)
			{
				if (myCollisionObjects[i].GetColliderType() == ColliderType::CircleCollider &&
					aCollider.myCollisionObjects[j].GetColliderType() == ColliderType::CircleCollider)
				{
					if (CircleToCircleCollision(myCollisionObjects[i], aCollider.myCollisionObjects[j]))
					{
						return true;
					}
				}
				if (myCollisionObjects[i].GetColliderType() == ColliderType::BoxCollider &&
					aCollider.myCollisionObjects[j].GetColliderType() == ColliderType::BoxCollider)
				{
					if (AABBToAABBCollision(myCollisionObjects[i], aCollider.myCollisionObjects[j]))
					{
						return true;
					}
				}
				if (myCollisionObjects[i].GetColliderType() == ColliderType::CircleCollider &&
					aCollider.myCollisionObjects[j].GetColliderType() == ColliderType::BoxCollider)
				{
					if (CircleToAABBCollision(myCollisionObjects[i], aCollider.myCollisionObjects[j]))
					{
						return true;
					}
				}
			}
		}
		return false;
	}

	bool Collider::Contains(const Collider& aCollider)
	{
		return false;
	}
	bool Collider::CircleToCircleCollision(CollisionObject& aFirstCollisionObject, CollisionObject& aSecondCollisionObject)
	{
		float deltaX = aFirstCollisionObject.GetPosition().x - aSecondCollisionObject.GetPosition().x;
		float deltaY = aFirstCollisionObject.GetPosition().y - aSecondCollisionObject.GetPosition().y;

		float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
		
		if (distance < aFirstCollisionObject.GetRadius() + aSecondCollisionObject.GetRadius())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool Collider::CircleToAABBCollision(CollisionObject& aCircleCollisionObject, CollisionObject& anAABBCollisionObject)
	{
		return false;
	}
	bool Collider::AABBToAABBCollision(CollisionObject& aFirstCollisionObject, CollisionObject& aSecondCollisionObject)
	{
		if (aFirstCollisionObject.GetPosition().x < aSecondCollisionObject.GetPosition().x + aSecondCollisionObject.GetWidth() &&
			aFirstCollisionObject.GetPosition().x + aFirstCollisionObject.GetWidth() > aSecondCollisionObject.GetPosition().x &&
			aFirstCollisionObject.GetPosition().y < aSecondCollisionObject.GetPosition().y + aSecondCollisionObject.GetHeight() &&
			aFirstCollisionObject.GetPosition().y + aFirstCollisionObject.GetHeight() > aSecondCollisionObject.GetPosition().y)
		{
			return true;
		}
		return false;
	}
}