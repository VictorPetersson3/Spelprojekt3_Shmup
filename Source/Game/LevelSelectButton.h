#pragma once
#include "ButtonElement.h"
namespace Studio
{
	class LevelSelectButton : public ButtonElement
	{
	public:
		LevelSelectButton(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag, const int aLayer);
		~LevelSelectButton();

		void Update() override;
		void OnClick() override;


	private:
		bool myIsClicked = false;

	};
}

