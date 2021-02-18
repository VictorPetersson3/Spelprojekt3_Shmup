#pragma once
#include "GameObject.h"
#include "SpriteSheet.h"
namespace Tga2D
{
	CSprite;
}
namespace Studio
{
	//Class Implementation
	class HealthBar : public GameObject
	{
	public:
		HealthBar() = default;
		HealthBar(const char* aImagePath, const VECTOR2F& aPosition, const int aLayer);
		HealthBar(const char* aImagePath, const VECTOR2F& aPosition, const int aLayer, Tga2D::CColor aColor);
		~HealthBar();

		void SetSizeX(const float aValue);
		void SetSizeY(const float aValue);
		void Update(Health& aHealthVariabel);
	protected:


	private:
		float myOriginalX;
		float myOriginalY;
		bool myHaveFrame;
		VECTOR2F myPosition;
		SpriteSheet myFrameSprite;

	};
}
