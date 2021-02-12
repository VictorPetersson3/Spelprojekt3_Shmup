#pragma once
#include "ButtonElement.h"

namespace Studio
{
	class ReturnToMainMenuButton : public ButtonElement
	{
	public:
		ReturnToMainMenuButton(const char* aSpritePath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag, int aLayer);
		~ReturnToMainMenuButton();

		void Update() override;
		void OnClick() override;

	private:
		float mySizeTimer;
		float mySize;
	};
}

