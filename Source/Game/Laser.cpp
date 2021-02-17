#include "stdafx.h"
#include "Laser.h"
#include "RendererAccessor.h"
#include "Renderer.h"
Studio::Laser::Laser(VECTOR2F aPosition) :
	GameObject("Sprites/assets/enemies/boss/laserSprite_02.dds")
{
	//Figure out a better way to do an offset...
	mySpriteSheet.SetAmountOfFrames({ 2, 16 });
	mySpriteSheet.PlayAnimationInRange(0.082333f, { 1, 1 }, { 2, 10 });
	myPosition = { aPosition.x -1250.0f, aPosition.y - 55.0f };
	myCollider.AddBoxColliderObject({ 0.0f, 0.0f }, { 2000.0f, 25.0f });
	myDamage = 0.0f;
	//mySpriteSheet.SetSizeRelativeToImage({ -1, 1 });
}

Studio::Laser::~Laser()
{
}

void Studio::Laser::Update(float anY)
{
	GameObject::Update({ myPosition.x, anY - 63.0f });
	if (!mySpriteSheet.IsAnimating())
	{
		mySpriteSheet.LoopAnimationInRange(0.082333f, { 1, 11 }, {2, 12 });
		myDamage = 1.0f;
	}
	RendererAccessor::GetInstance()->Render(*this);
}

float Studio::Laser::GetDamage()
{
	return myDamage;
}
