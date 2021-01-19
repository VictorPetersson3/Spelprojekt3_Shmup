#pragma once
#include "ButtonElement.h"
#include "RendererAccessor.h"
#include "Renderer.h"

namespace Studio
{
	class TestButton : public ButtonElement
	{
	public:
		TestButton(const char* aPath, VECTOR2F aPosition, VECTOR2F aSize, VECTOR2F aPivot);
		~TestButton();

		void Update() override;
		void OnClick() override;

		//void Render()override;
	};
}

