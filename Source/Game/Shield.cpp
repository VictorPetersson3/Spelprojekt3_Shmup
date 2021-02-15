#include "stdafx.h"
#include "Shield.h"
#include "HealthBar.h"
#include "tga2d/sprite/sprite.h"
#include "RendererAccessor.h"
#include "Renderer.h"
Studio::Shield::Shield(float aHitPoints) :
	GameObject("Sprites/assets/player/upgrades/effects/shieldSpriteRed.dds", aHitPoints),
	myHealthBar("Sprites/debugpixel.dds", { 700.0f, 100.0f }, 184, { 0.0f,0.0f,1.0f,0.5f })
{
	GameObject::GetSpriteSheet().GetSprite()->SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });
	mySpriteSheet.SetAmountOfFrames({ 4, 4 });
	mySpriteSheet.PlayAnimationInRange(0.082333f, { 1,2 }, { 3,2 });
	mySpriteSheet.SetLayer(3);
	mySpriteSheet.SetSizeRelativeToImage({1.2f,1.2f});
}

Studio::Shield::~Shield()
{
}

void Studio::Shield::Update(VECTOR2F aPosition)
{
	GameObject::Update({ aPosition.x - 20, aPosition.y });
	myHealthBar.Update(GetHealth());
	if (!mySpriteSheet.IsAnimating())
	{
		mySpriteSheet.LoopAnimationInRange(0.08233f, { 1,1 }, { 4,1 });
	}
	RendererAccessor::GetInstance()->Render(*this);
}

void Studio::Shield::HitLogic(float aDamage)
{
	TakeDamage(aDamage);
}

Studio::HealthBar* Studio::Shield::GetHealthBar()
{
	return &myHealthBar;
}
