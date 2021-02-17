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

		void CalculateButtonCollider();
		virtual void OnClick();
		virtual void Update();

		void SetPosition(VECTOR2F aPosition);

	protected:
		Tga2D::CSprite* mySprite;
		SpriteSheet* mySpriteSheet;
		float myLeft;
		float myRight;
		float myTop;
		float myBottom;

		float myOriginalSize;

		bool hasBeenHoveredOver = false;

		HWND myWindowHandle;
	};
}
