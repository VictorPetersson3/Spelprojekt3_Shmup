#pragma once
#include "SpriteSheet_AnimationData.h"


namespace Studio
{
	class TypePattern_Particle_SpriteSheet : public SpriteSheet_AnimationData
	{
	public:
		TypePattern_Particle_SpriteSheet(const std::string& aPath, const unsigned int aLayerOrder, const unsigned int aAmountOfFrames, const float aAnimationSpeed);
		~TypePattern_Particle_SpriteSheet();

		const unsigned int GetLayerOrder() const;
		Tga2D::CSprite* GetSprite();

	private:
		const unsigned int myLayerOrder;
	};
}


