#include "stdafx.h"
#include "GameObject.h"
namespace Studio
{
	GameObject::GameObject() : mySpriteSheet(nullptr)
	{
	}

	GameObject::GameObject(const std::string& anImagePath) :
		myHealth(100), // Maybe this should be set somewhere???
		mySpriteSheet(anImagePath.c_str())
	{
	}

	GameObject::GameObject(const std::string& anImagePath, const Tga2D::Vector2f& aAmountOfFrames) :
		myHealth(100),
		mySpriteSheet(anImagePath.c_str(), aAmountOfFrames)
	{
	}

	GameObject::GameObject(const std::string& anImagePath, float aHealthAmount) :
		myHealth(aHealthAmount), 
		mySpriteSheet(anImagePath.c_str())
	{
	}
	
	void GameObject::Update(const Tga2D::Vector2f& aPos)
	{
		myCollider.Update(aPos);
		mySpriteSheet.SetPosition(aPos);
		mySpriteSheet.UpdateAnimation();
		myPosition = aPos;
	}
	void GameObject::SetFrame(const Tga2D::Vector2f& aCurrentFrame)
	{
		mySpriteSheet.SetFrame(aCurrentFrame);
	}
	
	void GameObject::SetPosition(const Tga2D::Vector2f& aPos)
	{
		myPosition = aPos;
	}
	void GameObject::SetPositionX(const float aXVal)
	{
		myPosition.x = aXVal;
	}
	void GameObject::SetPositionY(const float aYVal)
	{
		myPosition.y = aYVal;
	}

	const Tga2D::Vector2f& GameObject::GetPosition()
	{
		return myPosition;
	}

	Tga2D::Vector2f* GameObject::GetPositionPointer()
	{
		return &myPosition;
	}


	Health& Studio::GameObject::GetHealth()
	{
		return myHealth;
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

	void GameObject::SetGodMode(bool aGodMode)
	{
		myHealth.SetGodMode(aGodMode);
	}

	SpriteSheet& GameObject::GetSpriteSheet()
	{
		return mySpriteSheet;
	}

	Collider& GameObject::GetCollider()
	{
		return myCollider;
	}
}
