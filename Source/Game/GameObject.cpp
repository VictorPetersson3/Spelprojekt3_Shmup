#include "stdafx.h"
#include "GameObject.h"
#include <tga2d/sprite/sprite.h>
#include "Timer.h"
#include "Renderer.h"
#include "RendererAccessor.h"
namespace Studio
{
	GameObject::GameObject() : mySpriteSheet(nullptr)
	{
	}

	GameObject::GameObject(const std::string& anImagePath) :
		myHealth(1), // Maybe this should be set somewhere???
		mySpriteSheet(anImagePath.c_str())
	{
	}

	GameObject::GameObject(const std::string& anImagePath, const Tga2D::Vector2f& aAmountOfFrames) :
		myHealth(1),
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

		// Visial hit effect
		myTimeSinceHit += DELTA_TIME;
		                   // 1.0f
		if (myTimeSinceHit < 0.25f && !myHealth.GetGodMode())
		{
			auto color = Tga2D::CColor(2550.0f, 2550.0f, 2550.0f, 1.0f);
			if (fmodf(myTimeSinceHit, 0.20f) > 0.10f)
			{
				color = Tga2D::CColor(2550.0f, 0.0f, 0.0f, 1.0f);
			}

			// Old code
			//auto color = Tga2D::CColor(1.0f, 1.0f, 1.0f, 1.0f);
			//color.myR = 1.0f / myTimeSinceHit;

			mySpriteSheet.GetSprite()->SetColor(color);
		}
		else
		{
			mySpriteSheet.GetSprite()->SetColor({ 1.0f, 1.0f, 1.0f, 1.f });
		}
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
		myTimeSinceHit = 0.0f;

		myHealth.TakeDamage(aDamage);

		if (aDamage > 0.0f)
		{
			// Test
			RendererAccessor::GetInstance()->ShakeCamera(2.0f, 0.125f);
		}
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
