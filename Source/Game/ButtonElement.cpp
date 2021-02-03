#include "stdafx.h"
#include "ButtonElement.h"
#include <iostream>

Studio::ButtonElement::ButtonElement()
{
	myBottom = 0;
	myTop = 0;
	myLeft = 0;
	myRight = 0;

	mySprite = nullptr;
}

Studio::ButtonElement::~ButtonElement()
{

}

void Studio::ButtonElement::OnClick()
{

}

void Studio::ButtonElement::Update()
{
		
}

void Studio::ButtonElement::SetPosition(VECTOR2F aPosition)
{
	mySpriteSheet->SetPosition(aPosition);
}
