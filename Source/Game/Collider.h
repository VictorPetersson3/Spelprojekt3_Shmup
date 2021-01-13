#pragma once
#include "CollisionObject.h"
#include <vector>
namespace Studio
{
	class Collider
	{
	public:
		void AddColliderObject(CollisionObject& aCollisionObject);
		// Not implemented
		bool Intersects(Collider& aCollider);
		// Not implemented
		bool Contains(const Collider& aCollider);

		bool CircleToCircleCollision(CollisionObject& aFirstCollisionObject, CollisionObject& aSecondCollisionObject);

		bool CircleToAABBCollision(CollisionObject& aCircleCollisionObject, CollisionObject& anAABBCollisionObject);

		bool AABBToAABBCollision(CollisionObject& aFirstCollisionObject, CollisionObject& aSecondCollisionObject);
	private:
		std::vector<CollisionObject> myCollisionObjects;

	};
}
