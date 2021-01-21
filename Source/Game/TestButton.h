#pragma once
#include "ButtonElement.h"
#include "RendererAccessor.h"
#include "Renderer.h"

namespace Studio
{
	class TestButton : public ButtonElement
	{
	public:
		TestButton();
		TestButton(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag);
		~TestButton();

		void Update() override;
		void OnClick() override;

		bool myIsClicked = false;
	};
}

