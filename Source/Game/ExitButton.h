#pragma once
#include "ButtonElement.h"
namespace Studio
{
	class ExitButton : public ButtonElement
	{
	public:
		ExitButton(const char* aSpritePath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag, int aLayer);
		~ExitButton();

		void Update() override;
		void OnClick() override;

	private:
		float mySizeTimer;
		float mySize;
	};
}


