#pragma once
#include "ButtonElement.h"
#include "Enums.h"

namespace Studio
{
	class ShopButtonTier2 : public ButtonElement
	{
	public:
		ShopButtonTier2(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, int aLayer, Enums::Tier2Upgrades aUpgradeType, int aCost,const char* aDescription);
		~ShopButtonTier2();

		void Update() override;
		void OnClick() override;
		void Reset();

	private:
		bool myIsClicked = false;
		bool myHasBeenPurchased = false;

		Enums::Tier2Upgrades myUpgradeType;
		std::string myDescription;

		int myCost;
	};
}


