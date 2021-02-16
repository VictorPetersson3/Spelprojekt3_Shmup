#pragma once
#include "ButtonElement.h"
#include "RendererAccessor.h"
#include "Renderer.h"
#include "PlayerAccessor.h"
#include "Enums.h"
#include "ScoreAccessor.h"
#include <string>

namespace Studio
{
	class ShopButton : public ButtonElement
	{
	public:
		ShopButton(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, int aLayer,Enums::Tier1Upgrades aUpgradeType,int aCost, char* aDescription, char* aName);
		~ShopButton();

		void Update() override;
		void OnClick() override;
		void Reset();

	private:
		bool myIsClicked = false;
		bool myHasBeenPurchased = false;
		Enums::Tier1Upgrades myUpgradeType;
		char* myDescription;
		char* myName;
		int myCost;

		float mySizeTimer;
		float mySize;
	};
}
