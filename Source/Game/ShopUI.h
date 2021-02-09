#pragma once
#include "UIElement.h"
#include "ImageElement.h"
#include "ButtonElement.h"
#include "TextElement.h"
#include "ShopButton.h"
#include "ShopButtonTier2.h"
#include "ShopButtonTier3.h"

#include <vector>

namespace Studio
{
	class ShopUI
	{
		std::vector<ButtonElement> myActiveButtons;
		std::vector<ButtonElement*> myActiveButtonPtrs;

		std::vector<ShopButton*> myTier1Buttons;
		std::vector<ShopButtonTier2*> myTier2Buttons;
		std::vector<ShopButtonTier3*> myTier3Buttons;

		int GetRandomNumberInRange(int max);

	public:
		ShopUI();
		~ShopUI();

		void ResetButtons();

		std::vector<ButtonElement*> GetShopButtons();
	};
}


