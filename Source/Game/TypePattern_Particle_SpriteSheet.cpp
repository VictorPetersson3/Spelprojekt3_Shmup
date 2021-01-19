#include "stdafx.h"
#include "TypePattern_Particle_SpriteSheet.h"

Studio::TypePattern_Particle_SpriteSheet::TypePattern_Particle_SpriteSheet(const std::string& aPath, const unsigned int aLayerOrder, const unsigned int aAmountOfFrames, const float aAnimationSpeed) :
	myLayerOrder(aLayerOrder),
	SpriteSheet_AnimationData(aPath, aAmountOfFrames, aAnimationSpeed)
{
}

Studio::TypePattern_Particle_SpriteSheet::~TypePattern_Particle_SpriteSheet()
{
	SpriteSheet_AnimationData::~SpriteSheet_AnimationData();
}

const unsigned int Studio::TypePattern_Particle_SpriteSheet::GetLayerOrder() const
{
	return myLayerOrder;
}

Tga2D::CSprite* Studio::TypePattern_Particle_SpriteSheet::GetSprite()
{
	return SpriteSheet_AnimationData::GetSprite();
}
