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
		ButtonElement(const char* aID,const char* aPath, VECTOR2F aPosition, VECTOR2F aSize);
		~ButtonElement();
		bool IsClicked() override;

		void Render()override;

		void Update()override;
		void OnClick()override;

		void ResetButton();

	private:
		Tga2D::CSprite* mySprite;

		std::string myId;

		float myLeft;
		float myRight;
		float myTop;
		float myBottom;

		bool myHasBeenClicked = false;

		Studio::RenderCommand myRenderCommand;
	};
}

