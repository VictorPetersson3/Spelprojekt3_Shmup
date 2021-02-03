#include "stdafx.h"
#include "Shield.h"
#include "HealthBar.h"
#include "tga2d/sprite/sprite.h"

Studio::Shield::Shield(float aHitPoints) :
	GameObject("Sprites/debugpixel.dds", aHitPoints),
	myHealthBar("Sprites/debugpixel.dds", { 700.0f, 150.0f }, 14, { 0.0f,0.0f,1.0f,1.0f })
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
