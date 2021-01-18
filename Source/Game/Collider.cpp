#include "stdafx.h"
#include "Collider.h"
#include <iostream>
namespace Studio
{
	Collider::Collider()
	{

	}

	void Collider::AddBoxColliderObject(Tga2D::Vector2f aPosition, Tga2D::Vector2f aColliderSize)
	{
		myCollisionObjects.push_back(CollisionObject(aPosition, aColliderSize));
	}

	void Collider::AddCircleColliderObject(Tga2D::Vector2f aPosition, float aRadius)
	{
		myCollisionObjects.push_back(CollisionObject(aPosition, aRadius));
	}

	void Collider::Update(const Tga2D::Vector2f& aPosition)
	{
		for (CollisionObject& collision : myCollisionObjects)
		{
			collision.Update(aPosition);
		}


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
					if (CircleToCircleIntersect(myCollisionObjects[i], aCollider.myCollisionObjects[j]))
					{
						return true;
					}
				}
				if (myCollisionObjects[i].GetColliderType() == ColliderType::BoxCollider &&
					aCollider.myCollisionObjects[j].GetColliderType() == ColliderType::BoxCollider)
				{
					if (AABBToAABBIntersect(myCollisionObjects[i], aCollider.myCollisionObjects[j]))
					{
						return true;
					}
				}
				if (myCollisionObjects[i].GetColliderType() == ColliderType::CircleCollider &&
					aCollider.myCollisionObjects[j].GetColliderType() == ColliderType::BoxCollider)
				{
					if (CircleToAABBIntersect(myCollisionObjects[i], aCollider.myCollisionObjects[j]))
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
	void Collider::Render()
	{
		for (CollisionObject& collision : myCollisionObjects)
		{
			if (flag)
			{
				if (collision.GetColliderType() == ColliderType::BoxCollider)
				{
					Tga2D::Vector2f lowerLeft({ collision.GetPosition().myX - collision.GetWidth() / 2, collision.GetPosition().myY + collision.GetHeight() / 2 });
					Tga2D::Vector2f lowerRight({ collision.GetPosition().myX + collision.GetWidth() / 2, collision.GetPosition().myY + collision.GetHeight() / 2 });
					Tga2D::Vector2f upperLeft({ collision.GetPosition().myX - collision.GetWidth() / 2, collision.GetPosition().myY - collision.GetHeight() / 2 });
					Tga2D::Vector2f upperRight({ collision.GetPosition().myX + collision.GetWidth() / 2, collision.GetPosition().myY - collision.GetHeight() / 2 });
					Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine((lowerLeft), (lowerRight), Tga2D::CColor({ 0.3f, 0.3f, 0.3f, 1.0f }));
					Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine((lowerRight), (upperRight), Tga2D::CColor({ 0.3f, 0.3f, 0.3f, 1.0f }));
					Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine((upperRight), (upperLeft), Tga2D::CColor({ 0.3f, 0.3f, 0.3f, 1.0f }));
					Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine((upperLeft), (lowerLeft), Tga2D::CColor({ 0.3f, 0.3f, 0.3f, 1.0f }));
				}
				if (collision.GetColliderType() == ColliderType::CircleCollider)
				{
					Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawCircle(collision.GetPosition(), collision.GetRadius()/2.0f, { 0.3f, 0.7f, 0.3f, 1.0f });
				}
			}
		}
	}
	bool Collider::CircleToCircleIntersect(CollisionObject& aFirstCollisionObject, CollisionObject& aSecondCollisionObject)
	{
		float deltaX = aSecondCollisionObject.GetPosition().x - aFirstCollisionObject.GetPosition().x;
		float deltaY = aSecondCollisionObject.GetPosition().y - aFirstCollisionObject.GetPosition().y;

		float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

		if (distance < aFirstCollisionObject.GetRadius() + aSecondCollisionObject.GetRadius())
		{
			return true;
		}
		return false;
	}
	bool Collider::CircleToAABBIntersect(CollisionObject& aCircleCollisionObject, CollisionObject& anAABBCollisionObject)
	{
		return false;
	}
	bool Collider::AABBToAABBIntersect(CollisionObject& aFirstCollisionObject, CollisionObject& aSecondCollisionObject)
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