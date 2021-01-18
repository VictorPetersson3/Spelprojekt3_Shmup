#pragma once
#include <string>
#include "Collider.h"

namespace Studio
{
	class UIElement
	{
	public:
		UIElement();
		~UIElement() = default;

		virtual void Update();

		virtual bool IsClicked();
		virtual void Render();
		virtual void OnClick();

		void SetActive(bool aState);
		void SetTag(const char* aTag);
		bool HasTag(const char* aTag);

	protected:
		std::string tag;
		bool myIsEnabled = false;
	};
}

