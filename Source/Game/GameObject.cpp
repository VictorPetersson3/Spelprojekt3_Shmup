#include "stdafx.h"
#include "GameObject.h"
namespace Studio
{
	// Deprecated. See GameObject.h for further details
	GameObject::GameObject(Tga2D::CSprite* aSprite) : myRenderCommand(aSprite),
		myHealth(100)
		,mySpriteSheet(nullptr) // This is bad
	{
	}

	// Deprecated. See GameObject.h for further details
	GameObject::GameObject(Tga2D::CSprite* aSprite, const Tga2D::Vector2f& aSize) : myRenderCommand(aSprite, aSize),
		myHealth(100)
		,mySpriteSheet(nullptr) // This is bad
	{
	}

	GameObject::GameObject(const std::string& anImagePath) :
		myHealth(100), // Maybe this should be set somewhere???
		mySpriteSheet(anImagePath.c_str())
	{
	}
	
	void GameObject::Update(const Tga2D::Vector2f& aPos)
	{
		myRenderCommand.Update(aPos);
		myCollider.Update(aPos);
		mySpriteSheet.myPosition = aPos;
	}
	void GameObject::Update(const Tga2D::Vector2f& aPos, const Tga2D::Vector2f& aTexRecTopL, const Tga2D::Vector2f& aTexRecBotR)
	{
		myRenderCommand.Update(aPos, aTexRecTopL, aTexRecBotR);
	}

	void GameObject::Rotate(const float aRotationInRadians)
	{
		myRenderCommand.Rotate(aRotationInRadians);
	}
	void GameObject::RotateRight(const float aRotationInRadians)
	{
		myRenderCommand.RotateRight(aRotationInRadians);
	}
	void GameObject::RotateLeft(const float aRotationInRadians)
	{
		myRenderCommand.RotateLeft(aRotationInRadians);
	}
	void GameObject::SetRotation(float aRotationInRadians)
	{
		myRenderCommand.SetRotation(aRotationInRadians);
	}
	const float GameObject::GetRotation() const
	{
		return myRenderCommand.GetRotation();
	}

	Sprite& Studio::GameObject::GetSprite()
	{
		return mySprite;
	}

	Health& Studio::GameObject::GetHealth()
	{
		return myHealth;
	}

	Studio::RenderCommand& GameObject::GetRenderCommand() 
	{
		return myRenderCommand;
	}

	bool GameObject::Intersects(GameObject& aGameObject)
	{
		return myCollider.Intersects(aGameObject.myCollider);
	}
	bool GameObject::Contains(const GameObject& aGameObject)
	{
		return myCollider.Contains(aGameObject.myCollider);
	}

	//Define SHOW_COLLISION to enable
	void GameObject::RenderDebugCollider() 
	{
		myCollider.Render();
	}

	void GameObject::TakeDamage(const float aDamage)
	{
		myHealth.TakeDamage(aDamage);
	}

	const float GameObject::GetMaxHealth()
	{
		return myHealth.GetMaxHealth();
	}

	const float GameObject::GetCurrentHealth()
	{
		return myHealth.GetCurrentHealth();
	}

	const bool GameObject::IsDead()
	{
		return myHealth.IsDead();
	}

	void GameObject::SetGodMode()
	{
		myHealth.SetGodMode();
	}

	const SpriteSheet& GameObject::GetSpriteSheet() const
	{
		return mySpriteSheet;
	}

	Collider& GameObject::GetCollider()
	{
		return myCollider;
	}
}
