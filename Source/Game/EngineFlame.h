#pragma once
#include "GameObject.h"

namespace Studio
{
	class EngineFlame : public GameObject
	{
	public:
		EngineFlame(const char* aImagePath, const Tga2D::Vector2f& aAmountOfFrames, const Tga2D::Vector2f& aPosition);
		~EngineFlame() = default;
		void Update(int aCurrentState, const Tga2D::Vector2f& aPosition);
	};
}