#pragma once
#include "CollisionObject.h"
#include <vector>
namespace Studio
{
	class Collider
	{
	public:
		Collider() = default;

		void AddBoxColliderObject(const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aColliderSize);

		void AddCircleColliderObject(const Tga2D::Vector2f& aPosition, float aRadius);

		void Update(const Tga2D::Vector2f& aPosition);
		// Not implemented
		bool Intersects(Collider& aCollider);
		// Not implemented
		bool Contains(const Collider& aCollider);

		void Render();

	private:
		bool CircleToCircleIntersect(CollisionObject& aFirstCollisionObject, CollisionObject& aSecondCollisionObject);

		bool CircleToAABBIntersect(CollisionObject& aCircleCollisionObject, CollisionObject& anAABBCollisionObject);

		bool AABBToAABBIntersect(CollisionObject& aFirstCollisionObject, CollisionObject& aSecondCollisionObject);

		std::vector<CollisionObject> myCollisionObjects;

		bool flag
#ifdef SHOW_COLLISION
			= true
#endif // SHOW_COLLISION
			;
	};
}
