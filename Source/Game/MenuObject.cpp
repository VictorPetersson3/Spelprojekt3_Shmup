#include "stdafx.h"
#include "MenuObject.h"

Studio::MenuObject::MenuObject()
{
}

Studio::MenuObject::~MenuObject()
{
}

void Studio::MenuObject::Enable()
{
	for (UIElement* e : myElements)
	{
		e->SetActive(true);
	}
}

void Studio::MenuObject::Disable()
{
	for (UIElement* e : myElements)
	{
		e->SetActive(false);
	}
}

void Studio::MenuObject::Add(UIElement* aElementToAdd)
{
	myElements.push_back(aElementToAdd);
}

void Studio::MenuObject::Update()
{
	for (UIElement* e : myElements)
	{		
		e->Update();	
	}
}

Studio::UIElement* Studio::MenuObject::GetElementWithTag(const char* aTag)
{
	for (UIElement* e : myElements)
	{
		if (e->HasTag(aTag))
		{
			return e;
		}
	}
}
