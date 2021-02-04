#pragma once
#include <string>
#include "RenderCommand.h"

namespace Studio
{
	class UIElement
	{
	public:
		UIElement();
		~UIElement() = default;

		bool IsClicked();
		void Render();
	
		virtual void OnClick();
		virtual void Update();

		void SetActive(bool aState);
		void SetTag(const char* aTag);
		bool HasTag(const char* aTag);
		bool myIsClicked = false;

	protected:
		std::string tag;
		bool myIsEnabled = false;

		float renderAspect = 1.51515f;
		float renderAspectY = 0;

		RenderCommand myRenderCommand;
	};
}

