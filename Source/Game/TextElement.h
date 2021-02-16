#pragma once
#include "UIElement.h"
#include "tga2d/text/text.h"


namespace Studio
{
	class TextElement : public UIElement
	{
	public:
		TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag);
		TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag, bool aIsCentered);

		TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag, Tga2D::CColor aTextColor);
		TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag, Tga2D::CColor aTextColor, bool aIsCentered);

		TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag, Tga2D::CColor aTextColor, const char* aFont);
		TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag, Tga2D::CColor aTextColor, const char* aFont, bool aIsCentered);



		~TextElement();

		void Render();
		void SetText(std::string& aText);
		void SetText(const char* aText);



	private:
		Tga2D::CText* myText;
		bool myIsCentered = false;

		VECTOR2F myPosToCenterAround;
	};
}

