#include "stdafx.h"
#include "EffectExplosionLarge.h"

Studio::EffectExplosionLarge::EffectExplosionLarge(const std::string& aImagePath, const Tga2D::Vector2f& aAmountOfFrames, const Tga2D::Vector2f& aPosition):
	GameObject(aImagePath, aAmountOfFrames)
{
	GameObject::SetPosition(aPosition);
	GameObject::mySpriteSheet.PlayAnimationInRange(0.083, { 1,1 }, {6, 1});
	GameObject::mySpriteSheet.SetLayer(10);
	printf("SpawnedExplosion\n");
}


void Studio::EffectExplosionLarge::Update()
{
	GameObject::Update(GameObject::GetPosition());
	//printf("Exploding Right now\n");

}

const bool Studio::EffectExplosionLarge::IsAnimating() const
{
	return GameObject::mySpriteSheet.IsAnimating();
}
