#pragma once
#include "GameObject.h"
namespace Studio
{
	class EffectExplosionLarge : public GameObject
	{
	public:
		EffectExplosionLarge(const std::string& aImagePath, const Tga2D::Vector2f& aAmountOfFrames, const Tga2D::Vector2f& aPosition);
		~EffectExplosionLarge() = default;
		//void PlayAnimation(int aCurrentState, const Tga2D::Vector2f & aPosition);
		void Update();
		const bool IsAnimating() const;
	};
}


