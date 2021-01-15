#pragma once
#include <string>

namespace Studio
{
	class UIElement
	{
	public:
		UIElement();
		~UIElement() = default;

		virtual bool IsClicked();
		virtual void Render();
	
		void SetActive(bool aState);
		void SetTag(const char* aTag);
		bool HasTag(const char* aTag);

	protected:
		std::string tag;
		bool myIsEnabled = false;
	};
}

