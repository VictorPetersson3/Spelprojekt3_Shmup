#pragma once
#include "ButtonElement.h"

namespace Studio
{
	class GodModeButton : public ButtonElement
	{
	public:
		GodModeButton();
		GodModeButton(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag);
		~GodModeButton();


		void Update() override;
		void OnClick() override;

		bool myIsClicked = false;
	};
}



