#pragma once
#include "Health.h"
#include "RenderCommand.h"
#include "Sprite.h"
#include "Collider.h"

// TODO: ^ Avoid this?
namespace Tga2D
{
	class CSprite;
}
namespace Studio
{
	class GameObject
	{
	private:
		Sprite mySprite;
		Collider myCollider;
		Health myHealth;
		RenderCommand myRenderCommand;

	public:
		GameObject() = default;
		GameObject(Tga2D::CSprite* aSprite);
		GameObject(Tga2D::CSprite* aSprite, const Tga2D::Vector2f& aSize);
		virtual ~GameObject() = default;
		virtual void Update(const Tga2D::Vector2f& aPos);


		// Temporary accessor for mySprite. DO NOT USE IN RETAIL
		Sprite& GetSprite();	 // Temporary accesser
		// Temporary accessor for myHealth. DO NOT USE IN RETAIL
		Health& GetHealth();	 // Temporary accesser

		#pragma region Sprite Specific
		// TODO: Steal public stuff from Sprite.h
		Studio::RenderCommand& GetRenderCommand();
		#pragma endregion

		#pragma region Collider Specific
		bool Intersects(GameObject& aGameObject);
		bool Contains(const GameObject& aGameObject);
		void RenderDebugCollider();

		Collider& GetCollider();
		#pragma endregion

		#pragma region Health Specific
		// TODO: Steal public stuff from Health.h
		#pragma endregion
	};
}

