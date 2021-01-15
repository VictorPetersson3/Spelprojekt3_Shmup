#include "stdafx.h"
#include "UIElement.h"

Studio::UIElement::UIElement()
{
}

bool Studio::UIElement::IsClicked()
{
    return false;
}

void Studio::UIElement::Render()
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
