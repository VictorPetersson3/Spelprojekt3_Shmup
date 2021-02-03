#pragma once
#include "Health.h"
#include "RenderCommand.h"
#include "Sprite.h"
#include "Collider.h"
#include "SpriteSheet.h"
// TODO: ^ Avoid this?
namespace Tga2D
{
	class CSprite;
}
namespace Studio
{
	class GameObject
	{
	protected:
		Collider myCollider;
		Health myHealth;
		Tga2D::Vector2f myPosition;

		#pragma region New Image Stuff (SpriteBatching)
		SpriteSheet mySpriteSheet;
		#pragma endregion

	public:
		GameObject();

		
		GameObject(const std::string& anImagePath);
		GameObject(const std::string& anImagePath, const Tga2D::Vector2f& aAmountOfFrames);
		GameObject(const std::string& anImagePath, float aHealthAmount);

		virtual ~GameObject() = default;
		void Update(const Tga2D::Vector2f& aPos);
		void SetFrame(const Tga2D::Vector2f& aCurrentFrame);

		const Tga2D::Vector2f& GetPosition();
		Tga2D::Vector2f* GetPositionPointer();

	
		void SetPosition(const Tga2D::Vector2f& aPos);
		void SetPositionX(const float aXVal);
		void SetPositionY(const float aYVal);

		// Temporary accessor for myHealth. DO NOT USE IN RETAIL
		Health& GetHealth();	 // Temporary accesser

		#pragma region Collider Specific
		bool Intersects(GameObject& aGameObject);
		bool Contains(const GameObject& aGameObject);
		void RenderDebugCollider();

		Collider& GetCollider();
		#pragma endregion

		#pragma region Health Specific
		// TODO: Steal public stuff from Health.h
		void TakeDamage(const float aDamage);
		const float GetMaxHealth();
		const float GetCurrentHealth();
		const bool IsDead();
		
		void SetGodMode(bool aGodMode);
		#pragma endregion

		#pragma region New Image Stuff (SpriteBatching)
		SpriteSheet& GetSpriteSheet();
		#pragma endregion
	};
}

