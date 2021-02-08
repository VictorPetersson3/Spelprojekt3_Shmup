#pragma once
#include "ButtonElement.h"
#include "Enums.h"

namespace Studio
{
	class ShopButtonTier2 : public ButtonElement
	{
		ShopButtonTier2(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, int aLayer, Enums::Tier2Upgrades aUpgradeType, int aCost);
		~ShopButtonTier2();

		void Update() override;
		void OnClick() override;

	private:
		bool myIsClicked = false;
		Enums::Tier2Upgrades myUpgradeType;

		int myCost;
	};
}


