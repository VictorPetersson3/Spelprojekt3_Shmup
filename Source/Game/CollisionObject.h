#pragma once
namespace Studio
{
	enum class ColliderType
	{
		CircleCollider,
		BoxCollider,
		NoCollider
	};
	class CollisionObject
	{
	public:
		CollisionObject();
		CollisionObject(const Tga2D::Vector2f& aPosition, float aRadius);
		CollisionObject(const Tga2D::Vector2f& aPosition, Tga2D::Vector2f aColliderSize);
		~CollisionObject() = default;
		void Update(const Tga2D::Vector2f& aPosition);
		float const GetWidth();
		float const GetHeight();
		float const GetRadius();
		ColliderType& GetColliderType();
		Tga2D::Vector2f GetPosition();
	private:
		float myWidth = 0;
		float myHeight = 0;
		float myRadius = 0;
		Tga2D::Vector2f myPosition;
		Tga2D::Vector2f mySpawnPosition;
		ColliderType myColliderType;
	};
}
