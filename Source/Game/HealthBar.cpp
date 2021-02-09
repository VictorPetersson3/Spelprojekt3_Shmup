#include "stdafx.h"
#include "HealthBar.h"
#include "Health.h"
#include "Renderer.h"
#include "RendererAccessor.h"
#include "tga2d/sprite/sprite.h"

namespace Studio
{
	HealthBar::HealthBar(const char* aImagePath, const VECTOR2F& aPosition, const int aLayer) :
		HealthBar::GameObject(aImagePath)
	{
		GameObject::GetSpriteSheet().SetPosition(aPosition);
		GameObject::GetSpriteSheet().GetSprite()->SetColor({ 1.0f,0.0f,0.0f,1.0f });
		GameObject::GetSpriteSheet().SetPivot({0.0f, 0.5f});
		GameObject::GetSpriteSheet().SetLayer(aLayer);
		SetGodMode(true);
		myOriginalX = 450.0f;
		myOriginalY = 25.0f;
	}

	HealthBar::HealthBar(const char* aImagePath, const VECTOR2F& aPosition, const int aLayer, Tga2D::CColor aColor) :
		HealthBar::GameObject(aImagePath)
	{
		GameObject::GetSpriteSheet().SetPosition(aPosition);
		GameObject::GetSpriteSheet().GetSprite()->SetColor({ aColor });
		GameObject::GetSpriteSheet().SetPivot({ 0.0f, 0.5f });
		GameObject::GetSpriteSheet().SetLayer(aLayer);
		SetGodMode(true);
		myOriginalX = 450.0f;
		myOriginalY = 25.0f;
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
		float percentage = aHealthVariabel.GetCurrentHealth() / aHealthVariabel.GetMaxHealth();
		GameObject::GetSpriteSheet().SetSize({ myOriginalX * percentage, myOriginalY });
		Studio::RendererAccessor::GetInstance()->Render(*this);
	}

}
