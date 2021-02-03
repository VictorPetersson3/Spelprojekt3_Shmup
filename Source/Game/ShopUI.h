#pragma once
#include "UIElement.h"
#include "ImageElement.h"
#include "ButtonElement.h"
#include "TextElement.h"
#include "ShopButton.h"

#include <vector>

namespace Studio
{
	class ShopUI
	{
		std::vector<ButtonElement> myActiveButtons;
		std::vector<ShopButton*> myActiveButtonPtrs;

		std::vector<ShopButton*> myTier1Buttons;
		std::vector<ShopButton*> myTier2Buttons;
		std::vector<ShopButton*> myTier3Buttons;

		int GetRandomNumberInRange(int max);

	public:
		ShopUI();
		~ShopUI();

		std::vector<ShopButton*> GetShopButtons();
	};
}


