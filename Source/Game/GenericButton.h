#pragma once
#include "ButtonElement.h"
namespace Studio
{
	class GenericButton : public ButtonElement
	{
	public:
		GenericButton(const char* aSpritePath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag, int aLayer);
		~GenericButton();

		void Update() override;
		void OnClick() override;

		bool IsClicked();

	private:

	};
}

