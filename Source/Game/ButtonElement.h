#pragma once
#include "UIElement.h"
#include "SpriteSheet.h"
#include <WinUser.h>

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
		SpriteSheet* mySpriteSheet;
		float myLeft;
		float myRight;
		float myTop;
		float myBottom;

		HWND myWindowHandle;
	};
}
