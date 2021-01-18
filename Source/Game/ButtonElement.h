#pragma once
#include "UIElement.h"
#include "RenderCommand.h"

namespace Tga2D
{
	class CSprite;
}

namespace Studio
{
	class ButtonElement : public UIElement
	{
	public:
		ButtonElement();
		ButtonElement(const char* aID,const char* aPath, VECTOR2F aPosition, VECTOR2F aSize, VECTOR2F aPivot);
		~ButtonElement();

		bool IsClicked() override;

		void Render()override;

		void ResetButton();

		void OnClick();

	protected:
		Tga2D::CSprite* mySprite;

		float myLeft;
		float myRight;
		float myTop;
		float myBottom;

		bool myHasBeenClicked = false;

		Studio::RenderCommand myRenderCommand;
	};
}

