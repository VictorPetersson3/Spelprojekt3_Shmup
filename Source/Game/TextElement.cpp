#include "stdafx.h"
#include "TextElement.h"


Studio::TextElement::TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag)
{
	myText = new Tga2D::CText("Text/arial.ttf", aFontSize);
	myText->SetPosition(aPosition);

	myText->SetColor(Tga2D::CColor{ 0,0,0,1 });
	tag = aTag;
}

Studio::TextElement::TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag, bool aIsCentered)
{
}

Studio::TextElement::TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag, Tga2D::CColor aTextColor)
{
	myText = new Tga2D::CText("Text/arial.ttf", aFontSize);
	myText->SetPosition(aPosition);

	myText->SetColor(aTextColor);
	tag = aTag;
}

Studio::TextElement::TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag, Tga2D::CColor aTextColor, bool aIsCentered)
{
	myText = new Tga2D::CText("Text/arial.ttf", aFontSize);
	myText->SetPosition(aPosition);

	myText->SetColor(aTextColor);
	tag = aTag;

	myPosToCenterAround = aPosition;

	myIsCentered = aIsCentered;

	
}

Studio::TextElement::TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag, Tga2D::CColor aTextColor, const char* aFont)
{
	myText = new Tga2D::CText(aFont, aFontSize);
	myText->SetPosition(aPosition);

	myText->SetColor(aTextColor);
	tag = aTag;

}

Studio::TextElement::TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag, Tga2D::CColor aTextColor, const char* aFont, bool aIsCentered)
{
	myText = new Tga2D::CText(aFont, aFontSize);
	myText->SetPosition(aPosition);

	myText->SetColor(aTextColor);
	tag = aTag;
	myPosToCenterAround = aPosition;

	myIsCentered = aIsCentered;
}

Studio::TextElement::~TextElement()
{
	delete myText;
	myText = nullptr;
}

void Studio::TextElement::Render()
{

	if (myIsEnabled == true)
	{
		myText->Render();
	}
	else
	{
		myText->SetText("");
	}
}

void Studio::TextElement::SetText(std::string& aText)
{
	if (myIsEnabled == true)
	{
		myText->SetText(aText);

		if (myIsCentered == true)
		{
			myText->SetPosition({ myPosToCenterAround.x - (myText->GetWidth() / 2),myText->GetPosition().y });
		}
	}
}

void Studio::TextElement::SetText(const char* aText)
{
	if (myIsEnabled == true)
	{
		myText->SetText(aText);

		if (myIsCentered == true)
		{
			myText->SetPosition({ myPosToCenterAround.x - (myText->GetWidth() / 2),myText->GetPosition().y });
		}
	}
}
