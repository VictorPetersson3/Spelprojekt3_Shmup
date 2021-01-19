#include "stdafx.h"
#include "SpriteSheet_AnimationData.h"
#include <tga2d/sprite/sprite.h>

Studio::SpriteSheet_AnimationData::SpriteSheet_AnimationData(const std::string& aPath, const unsigned int aAmountOfFrames, const float aAnimationSpeed) :
	myAmountOfFrames(aAmountOfFrames),
	myAnimationSpeed(aAnimationSpeed)
{
	mySprite = nullptr;
	mySprite = new Tga2D::CSprite(aPath.c_str());
	mySprite->SetPivot({ 0.5f, 0.5f });
	myRectSize = (static_cast<float>(mySprite->GetImageSize().x) / static_cast<float>(aAmountOfFrames)) / static_cast<float>(mySprite->GetImageSize().x);
}

Studio::SpriteSheet_AnimationData::~SpriteSheet_AnimationData()
{
	delete mySprite;
	mySprite = nullptr;
}

const unsigned int Studio::SpriteSheet_AnimationData::GetAmountOfFrames() const
{
	return myAmountOfFrames;
}

const float Studio::SpriteSheet_AnimationData::GetRectSize() const
{
	return myRectSize;
}

const float Studio::SpriteSheet_AnimationData::GetAnimationSpeed() const
{
	return myAnimationSpeed;
}

Tga2D::CSprite* Studio::SpriteSheet_AnimationData::GetSprite()
{
	return mySprite;
}
