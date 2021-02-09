#include "stdafx.h"
#include "MenuObject.h"
#include <Windows.h>

Studio::MenuObject::MenuObject()
{
}

Studio::MenuObject::~MenuObject()
{
}

void Studio::MenuObject::Enable()
{
	//Sleep(50);
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

void Studio::MenuObject::Clear()
{
	for (size_t i = 0; i < myElements.size(); i++)
	{
		myElements.erase(myElements.begin() + i);
	}
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
