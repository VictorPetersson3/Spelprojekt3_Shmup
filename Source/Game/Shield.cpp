#include "stdafx.h"
#include "Shield.h"
#include "HealthBar.h"
#include "tga2d/sprite/sprite.h"

Studio::Shield::Shield(float aHitPoints) :
	GameObject("Sprites/debugpixel.dds", aHitPoints),
	myHealthBar("Sprites/debugpixel.dds", { 700.0f, 100.0f }, 184, { 0.0f,0.0f,1.0f,0.5f })
{
	GameObject::GetSpriteSheet().GetSprite()->SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });
}

Studio::Shield::~Shield()
{
}

void Studio::Shield::Update()
{
	myHealthBar.Update(GetHealth());
}

void Studio::Shield::HitLogic(float aDamage)
{
	TakeDamage(aDamage);
}

Studio::HealthBar* Studio::Shield::GetHealthBar()
{
	return &myHealthBar;
}
