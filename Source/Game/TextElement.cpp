#include "stdafx.h"
#include "TextElement.h"


Studio::TextElement::TextElement(Tga2D::EFontSize aFontSize, VECTOR2F aPosition, const char* aTag)
{
	myText = new Tga2D::CText("Text/arial.ttf", aFontSize);
	myText->SetPosition(aPosition);

	myText->SetColor(Tga2D::CColor{ 0,0,0,1 });
	tag = aTag;
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
}

void Studio::TextElement::SetText(std::string& aText)
{
	myText->SetText(aText);
}
