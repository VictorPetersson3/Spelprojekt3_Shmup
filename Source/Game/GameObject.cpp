#include "stdafx.h"
#include "GameObject.h"
namespace Studio
{
	GameObject::GameObject(Tga2D::CSprite* aSprite) : myRenderCommand(aSprite)
	{
	}
	void GameObject::Update(const Tga2D::Vector2f& aPos)
	{
		myRenderCommand.Update(aPos);
		myCollider.Update(aPos);
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
}
