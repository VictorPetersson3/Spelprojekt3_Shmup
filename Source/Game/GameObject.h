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
		Sprite mySprite;
		Collider myCollider;
		Health myHealth;
		RenderCommand myRenderCommand;
		Tga2D::Vector2f myPosition;

		#pragma region New Image Stuff (SpriteBatching)
		SpriteSheet mySpriteSheet;
		#pragma endregion

	public:
		GameObject() = default;

		[[deprecated("Deprecated constructor. Use GameObject(const std::string& anImagePath) instead")]]
		GameObject(Tga2D::CSprite* aSprite);
		
		GameObject(const std::string& anImagePath);
		GameObject(const std::string& anImagePath, const Tga2D::Vector2f& aAmountOfFrames);
		GameObject(const std::string& anImagePath, float aHealthAmount);

		virtual ~GameObject() = default;
		void Update(const Tga2D::Vector2f& aPos);
		void SetFrame(const Tga2D::Vector2f& aCurrentFrame);
		void Update(const Tga2D::Vector2f& aPos, const Tga2D::Vector2f& aTexRecTopL, const Tga2D::Vector2f& aTexRecBotR);

		const float GetRotation() const;
		const Tga2D::Vector2f& GetPosition();

		void Rotate(const float aRotationInRadians);
		void RotateRight(const float aRotationInRadians);
		void RotateLeft(const float aRotationInRadians);
		void SetRotation(float aRotationInRadians);
		void SetPosition(const Tga2D::Vector2f& aPos);
		void SetPositionX(const float aXVal);
		void SetPositionY(const float aYVal);


		// Temporary accessor for mySprite. DO NOT USE IN RETAIL
		Sprite& GetSprite();	 // Temporary accesser
		// Temporary accessor for myHealth. DO NOT USE IN RETAIL
		Health& GetHealth();	 // Temporary accesser

		#pragma region Sprite Specific
		[[deprecated("Deprecated method. Use GameObject::SpriteSheet instead")]]
		// Deprecated, DO NOT USE
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

