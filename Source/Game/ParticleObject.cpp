#include "stdafx.h"
#include "ParticleObject.h"
#include "RendererAccessor.h"
#include "Renderer.h"
#include <iostream>
Studio::ParticleObject::ParticleObject(TypePattern_Particle_SpriteSheet* aTypeObject, const Tga2D::Vector2f& aSpawnPosition) :
	GameObject(aTypeObject->GetSprite()),
	myPosition(aSpawnPosition),
	mySprite(aTypeObject->GetSprite()),
	myTypeObject(aTypeObject)
{
	myCurrentFrame = 1;
	myLifeTime = 0;
	myRectRightSide = myTypeObject->GetRectSize();
	myFrameTime = myTypeObject->GetAnimationSpeed() / static_cast<float>(myTypeObject->GetAmountOfFrames());
	myAnimationHasFinished = false;
}

void Studio::ParticleObject::Update(float aDeltaTime)
{

	if (!myAnimationHasFinished)
	{
		myLifeTime += aDeltaTime;
		if (myLifeTime > myFrameTime * myCurrentFrame)
		{
			myCurrentFrame++;

			if (myCurrentFrame >= myTypeObject->GetAmountOfFrames())
			{
				myAnimationHasFinished = true;
			}
		}
		GameObject::Update(myPosition, 
			{ myRectRightSide * myCurrentFrame - myRectRightSide, 0 },
			{ myRectRightSide * myCurrentFrame, 1});
		Render();
	}
	
}

void Studio::ParticleObject::Render()
{
	Studio::RendererAccessor::GetInstance()->Render(*this);
}

const bool Studio::ParticleObject::GetHasFinishedAnimation() const
{
	return myAnimationHasFinished;
}

