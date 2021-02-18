#include "stdafx.h"
#include "HealthBar.h"
#include "Health.h"
#include "Renderer.h"
#include "RendererAccessor.h"
#include "tga2d/sprite/sprite.h"

namespace Studio
{
	HealthBar::HealthBar(const char* aImagePath, const VECTOR2F& aPosition, const int aLayer) :
		HealthBar::GameObject(aImagePath),
		myFrameSprite("Sprites/UI/BossFrameREAL.dds")
	{
		GameObject::GetSpriteSheet().SetPosition(aPosition);
		GameObject::GetSpriteSheet().GetSprite()->SetColor({ 1.0f,0.0f,0.0f,1.0f });
		GameObject::GetSpriteSheet().SetPivot({0.0f, 0.5f});
		GameObject::GetSpriteSheet().SetLayer(aLayer);
		myFrameSprite.SetPosition({ aPosition.x + 225.0f, aPosition.y - 27.0f});
		myFrameSprite.SetLayer(aLayer - 1);
		SetGodMode(true);
		myOriginalX = 450.0f;
		myOriginalY = 25.0f;
		myHaveFrame = true;
	}

	HealthBar::HealthBar(const char* aImagePath, const VECTOR2F& aPosition, const int aLayer, Tga2D::CColor aColor) :
		HealthBar::GameObject(aImagePath),
		myFrameSprite("Sprites/UI/BossFrameREAL.dds")
	{
		GameObject::GetSpriteSheet().SetPosition(aPosition);
		GameObject::GetSpriteSheet().GetSprite()->SetColor({ aColor });
		GameObject::GetSpriteSheet().SetPivot({ 0.0f, 0.5f });
		GameObject::GetSpriteSheet().SetLayer(aLayer);
		SetGodMode(true);
		myOriginalX = 450.0f;
		myOriginalY = 25.0f;
		myHaveFrame = false;
	}

	HealthBar::~HealthBar()
	{
	}

	void HealthBar::SetSizeX(const float aValue)
	{
		myOriginalX = aValue;
	}

	void HealthBar::SetSizeY(const float aValue)
	{
		myOriginalY = aValue;
	}

	void HealthBar::Update(Health& aHealthVariabel)
	{
		if (myHaveFrame)
		{
			Studio::RendererAccessor::GetInstance()->Render(myFrameSprite);
		}
		float percentage = aHealthVariabel.GetCurrentHealth() / aHealthVariabel.GetMaxHealth();
		GameObject::GetSpriteSheet().SetSize({ myOriginalX * percentage, myOriginalY });
		Studio::RendererAccessor::GetInstance()->Render(*this);
	}

}
