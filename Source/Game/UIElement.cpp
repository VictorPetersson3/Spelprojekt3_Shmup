#include "stdafx.h"
#include "UIElement.h"
#include <iostream>
Studio::UIElement::UIElement()
{
   
}

bool Studio::UIElement::IsClicked()
{
    return myIsClicked;
}

void Studio::UIElement::Render()
{
}

void Studio::UIElement::OnClick()
{

}

void Studio::UIElement::Update()
{

}

void Studio::UIElement::SetActive(bool aState)
{
    myIsEnabled = aState;
}

void Studio::UIElement::SetTag(const char* aTag)
{
    tag = aTag;
}

bool Studio::UIElement::HasTag(const char* aTag)
{
    if (tag == aTag)
    {
        return true;
    }
    return false;
}
