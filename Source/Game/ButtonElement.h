#pragma once
#include "UIElement.h"

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
		~ButtonElement();

		virtual void OnClick();
		virtual void Update();

	protected:
		Tga2D::CSprite* mySprite;
		float myLeft;
		float myRight;
		float myTop;
		float myBottom;
	};
}
