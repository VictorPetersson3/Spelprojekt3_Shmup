#pragma once
#include <vector>
#include "UIElement.h"
#include "ShopButton.h"

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

		void Clear();

		void Update();

		bool GetIsEnabled();

		UIElement* GetElementWithTag(const char* aTag);

	private:
		std::vector<UIElement*> myElements;
	};
}

