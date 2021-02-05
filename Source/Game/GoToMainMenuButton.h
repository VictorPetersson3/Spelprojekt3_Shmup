#pragma once
#include "ButtonElement.h"
namespace Studio
{
	class GoToMainMenuButton : public ButtonElement
	{
	public:
		GoToMainMenuButton(const char* aSpritePath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag, int aLayer);
		~GoToMainMenuButton();

		void Update()override;
		void OnClick()override;
	};
}


