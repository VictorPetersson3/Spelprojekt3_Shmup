#pragma once
#include "ButtonElement.h"
#include "RendererAccessor.h"
#include "Renderer.h"
#include "PlayerAccessor.h"
#include "Enums.h"
#include "ScoreAccessor.h"

namespace Studio
{
	class ShopButton : public ButtonElement
	{
	public:
		ShopButton(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, int aLayer,Enums::RapidFireUpgrades aUpgradeType,int aCost);
		~ShopButton();

		void Update() override;
		void OnClick() override;

	private:
		bool myIsClicked = false;
		Enums::RapidFireUpgrades myUpgradeType;

		int myCost;
	};
}
