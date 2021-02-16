#pragma once
#include "ButtonElement.h"
#include "Enums.h"

namespace Studio
{
	class ShopButtonTier3 : public ButtonElement
	{
	public:
		ShopButtonTier3(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, int aLayer, Enums::Tier3Upgrades aUpgradeType, int aCost, char* aDescription, char* aName);
		~ShopButtonTier3();

		void Update() override;
		void OnClick() override;

	private:
		bool myIsClicked = false;
		bool myHasBeenPurchased = false;
		Enums::Tier3Upgrades myUpgradeType;
		char* myDescription;

		char* myName;

		int myCost;

		float mySize;
		float mySizeTimer;
	};
}


