#include "stdafx.h"
#include "Collider.h"
#include <iostream>
#include <math.h>
namespace Studio
{
	void Collider::AddBoxColliderObject(const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aColliderSize)
	{
		myCollisionObjects.push_back(CollisionObject(aPosition, aColliderSize));
	}

	void Collider::AddCircleColliderObject(const Tga2D::Vector2f& aPosition, float aRadius)
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
				if (myCollisionObjects[i].GetColliderType() == ColliderType::BoxCollider &&
					aCollider.myCollisionObjects[j].GetColliderType() == ColliderType::CircleCollider)
				{
					if (CircleToAABBIntersect(aCollider.myCollisionObjects[j], myCollisionObjects[i]))
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
					//Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine((lowerLeft), (lowerRight), Tga2D::CColor({ 1.0f, 0.0f, 0.0f, 1.0f }));
					//Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine((lowerRight), (upperRight), Tga2D::CColor({ 1.0f, 0.0f, 0.0f, 1.0f }));
					//Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine((upperRight), (upperLeft), Tga2D::CColor({ 1.0f, 0.0f, 0.0f, 1.0f }));
					//Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawLine((upperLeft), (lowerLeft), Tga2D::CColor({ 1.0f, 0.0f, 0.0f, 1.0f }));
				}
				if (collision.GetColliderType() == ColliderType::CircleCollider)
				{
					Tga2D::CEngine::GetInstance()->GetDebugDrawer().DrawCircle(collision.GetPosition(), collision.GetRadius() / 2.0f, { 0.0f, 0.0f, 0.0f, 1.0f });
				}
			}
		}
	}
	bool Collider::CircleToCircleIntersect(CollisionObject& aFirstCollisionObject, CollisionObject& aSecondCollisionObject)
	{
		float deltaX = aSecondCollisionObject.GetPosition().x - aFirstCollisionObject.GetPosition().x;
		float deltaY = aSecondCollisionObject.GetPosition().y - aFirstCollisionObject.GetPosition().y;

		float distance = (deltaX * deltaX + deltaY * deltaY);

		if (distance < (aFirstCollisionObject.GetRadius() + aSecondCollisionObject.GetRadius()) * (aFirstCollisionObject.GetRadius() + aSecondCollisionObject.GetRadius()))
		{
			return true;
		}
		return false;
	}
	bool Collider::CircleToAABBIntersect(CollisionObject& aCircleCollisionObject, CollisionObject& anAABBCollisionObject)
	{
		//find the closest point on the AABB
		float closestPointX = aCircleCollisionObject.GetPosition().x
			, closestPointY = aCircleCollisionObject.GetPosition().y;

		if (aCircleCollisionObject.GetPosition().x < anAABBCollisionObject.GetPosition().x - anAABBCollisionObject.GetWidth() * 0.5f)
		{
			closestPointX = anAABBCollisionObject.GetPosition().x - anAABBCollisionObject.GetWidth() * 0.5f;
		}
		else if (aCircleCollisionObject.GetPosition().x > anAABBCollisionObject.GetPosition().x + anAABBCollisionObject.GetWidth() * 0.5f)
		{
			closestPointX = anAABBCollisionObject.GetPosition().x + anAABBCollisionObject.GetWidth() * 0.5f;
		}

		if (aCircleCollisionObject.GetPosition().y < anAABBCollisionObject.GetPosition().y - anAABBCollisionObject.GetHeight() * 0.5f)
		{
			closestPointY = anAABBCollisionObject.GetPosition().y - anAABBCollisionObject.GetHeight() * 0.5f;
		}
		else if (aCircleCollisionObject.GetPosition().y > anAABBCollisionObject.GetPosition().y + anAABBCollisionObject.GetHeight() * 0.5f)
		{
			closestPointY = anAABBCollisionObject.GetPosition().y + anAABBCollisionObject.GetHeight() * 0.5f;
		}

		float deltaX = aCircleCollisionObject.GetPosition().x - closestPointX;
		float deltaY = aCircleCollisionObject.GetPosition().y - closestPointY;


		float distance = deltaX * deltaX + deltaY * deltaY;

		if (distance < aCircleCollisionObject.GetRadius() * aCircleCollisionObject.GetRadius())
		{
			return true;
		}
		return false;
	}
	bool Collider::AABBToAABBIntersect(CollisionObject& aFirstCollisionObject, CollisionObject& aSecondCollisionObject)
	{
		if (aFirstCollisionObject.GetPosition().x - aFirstCollisionObject.GetWidth() * 0.5f > aSecondCollisionObject.GetPosition().x + aSecondCollisionObject.GetWidth() * 0.5f) return false;
		if (aFirstCollisionObject.GetPosition().x + aFirstCollisionObject.GetWidth() * 0.5f < aSecondCollisionObject.GetPosition().x - aSecondCollisionObject.GetWidth() * 0.5f) return false;
		if (aFirstCollisionObject.GetPosition().y - aFirstCollisionObject.GetHeight() * 0.5f > aSecondCollisionObject.GetPosition().y + aSecondCollisionObject.GetHeight() * 0.5f) return false;
		if (aFirstCollisionObject.GetPosition().y + aFirstCollisionObject.GetHeight() * 0.5f < aSecondCollisionObject.GetPosition().y - aSecondCollisionObject.GetHeight() * 0.5f) return false;

		return true;
	}
}