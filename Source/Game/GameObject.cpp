#include "stdafx.h"
#include "GameObject.h"
namespace Studio
{
	GameObject::GameObject(Tga2D::CSprite* aSprite) : myRenderCommand(aSprite)
	{
	}
	GameObject::GameObject(Tga2D::CSprite* aSprite, const Tga2D::Vector2f& aSize) : myRenderCommand(aSprite, aSize)
	{
	}
	
	void GameObject::Update(const Tga2D::Vector2f& aPos)
	{
		myRenderCommand.Update(aPos);
		myCollider.Update(aPos);
	}
	void GameObject::Update(const Tga2D::Vector2f& aPos, const Tga2D::Vector2f& aTexRecTopL, const Tga2D::Vector2f& aTexRecBotR)
	{
		myRenderCommand.Update(aPos, aTexRecTopL, aTexRecBotR);
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

	Collider& GameObject::GetCollider()
	{
		return myCollider;
	}
}
