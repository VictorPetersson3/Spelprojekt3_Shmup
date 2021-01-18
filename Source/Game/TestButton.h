#pragma once
#include "ButtonElement.h"

namespace Studio
{
	class TestButton : public ButtonElement
	{
		public:
			TestButton(const char* aID, const char* aPath, VECTOR2F aPosition, VECTOR2F aSize, VECTOR2F aPivot);
			//void OnClick() override;
	};
}

