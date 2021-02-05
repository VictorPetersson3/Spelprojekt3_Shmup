#pragma once
#include "GameObject.h"
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
		VECTOR2F myPosition;
		float myOriginalX;
		float myOriginalY;

	};
}
