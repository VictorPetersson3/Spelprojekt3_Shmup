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
		CollisionObject(Tga2D::Vector2f aPosition, Tga2D::Vector2f aColliderSize);
		CollisionObject(Tga2D::Vector2f aPosition, float aRadius);
		~CollisionObject() = default;

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
		ColliderType myColliderType;
	};
}
