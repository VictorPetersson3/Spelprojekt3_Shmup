#pragma once
#include "UIElement.h"
#include "SpriteSheet.h"

namespace Studio
{
	class ImageElement : public UIElement
	{
	public:
		ImageElement(const char* aPath, VECTOR2F aPosition, VECTOR2F aSize, VECTOR2F aPivot,int aLayer, const char* aTag);
		ImageElement(const char* aPath, VECTOR2F aPosition, VECTOR2F aSize, VECTOR2F aPivot, int aLayer, const char* aTag,Tga2D::CColor aColor);

		~ImageElement();
		void Update() override;

		void SetSprite(const char* aPath);

		SpriteSheet* GetSpriteSheet();


	private:
		SpriteSheet* mySpriteSheet;

	};
}

