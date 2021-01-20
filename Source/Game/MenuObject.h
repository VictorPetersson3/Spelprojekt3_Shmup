#pragma once
#include <vector>
#include "UIElement.h"

namespace Studio
{
	class MenuObject
	{
	public:
		MenuObject();
		~MenuObject();

		void Enable();
		void Disable();

		void Add(UIElement* aElementToAdd);

		void Update();

		UIElement* GetElementWithTag(const char* aTag);

	private:
		std::vector<UIElement*> myElements;
	};
}

