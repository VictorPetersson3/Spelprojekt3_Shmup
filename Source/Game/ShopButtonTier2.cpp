#include "stdafx.h"
#include "ShopButtonTier2.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include <iostream>
#include "AudioManagerAccesor.h"
#include "AudioManager.h"
#include <string>
#include "Renderer.h"
#include "RendererAccessor.h"
#include "ScoreAccessor.h"
#include "ScoreManager.h"
#include "PlayerAccessor.h"
#include "Player.h"
#include "MenuManager.h"
#include "MenuManagerSingleton.h"
#include "TextElement.h"
#include "ImageElement.h"
#include "Timer.h"

#define MOUSEPOS Studio::InputManager::GetInstance()->GetMousePosition()

Studio::ShopButtonTier2::ShopButtonTier2(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, int aLayer, Enums::Tier2Upgrades aUpgradeType, int aCost, char* aDescription, char* aName)
{
	mySprite = new Tga2D::CSprite(aPath);
	mySprite->SetPivot(aPivot);
	mySprite->SetSizeRelativeToImage(aSize);
	mySprite->SetPosition(aPosition);

	mySpriteSheet = new SpriteSheet(aPath);
	mySpriteSheet->SetPivot(aPivot);
	mySpriteSheet->SetPosition(aPosition);
	mySpriteSheet->SetSizeRelativeToImage(aSize);
	mySpriteSheet->SetLayer(aLayer);

	myUpgradeType = aUpgradeType;

	myCost = aCost;

	myDescription = aDescription;

	myName = aName;

	mySize = 1;
	mySizeTimer = 0;

	CalculateButtonCollider();

}

Studio::ShopButtonTier2::~ShopButtonTier2()
{
	delete mySprite;
	delete mySpriteSheet;
	mySprite = nullptr;
	mySpriteSheet = nullptr;
}

void Studio::ShopButtonTier2::Update()
{
	CalculateButtonCollider();

	if (mySizeTimer <= 0.05f && hasBeenHoveredOver)
	{
		mySize += Studio::Timer::GetInstance()->TGetDeltaTime();
		mySizeTimer += Studio::Timer::GetInstance()->TGetDeltaTime();
	}

	if (myIsEnabled == true)
	{
		if (myIsClicked == false)
		{
			if (MOUSEPOS.x >= myLeft && MOUSEPOS.x <= myRight)
			{
				if (MOUSEPOS.y >= myTop && MOUSEPOS.y <= myBottom)
				{
					if (!hasBeenHoveredOver)
					{
						AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonMouseOver.flac", false, 0.15f);
						MenuManagerSingleton::GetInstance()->GetShopDescriptionText()->SetActive(true);
						MenuManagerSingleton::GetInstance()->GetShopDescriptionText()->SetSprite(myDescription);

						std::string s = "Cost: " + myCost;

						hasBeenHoveredOver = true;

					}

					RendererAccessor::GetInstance()->Render(*MenuManagerSingleton::GetInstance()->GetShopDescriptionText()->GetSpriteSheet());

					if (Studio::InputManager::GetInstance()->GetMouseLPressed())
					{
						OnClick();
						myIsClicked = true;
					}
				}
				else
				{
					mySize = 1;
					mySizeTimer = 0;

					if (hasBeenHoveredOver)
					{
						MenuManagerSingleton::GetInstance()->GetShopCostText()->SetActive(false);
						MenuManagerSingleton::GetInstance()->GetShopUpgradeNameText()->SetActive(false);

					}

					hasBeenHoveredOver = false;
				}
			}
			else
			{
				mySize = 1;
				mySizeTimer = 0;

				if (hasBeenHoveredOver)
				{
					MenuManagerSingleton::GetInstance()->GetShopCostText()->SetActive(false);
					MenuManagerSingleton::GetInstance()->GetShopUpgradeNameText()->SetActive(false);

				}

				hasBeenHoveredOver = false;
			}
		}

		if (Studio::InputManager::GetInstance()->GetMouseLReleased() && myIsClicked)
		{
			myIsClicked = false;
		}

		mySpriteSheet->SetSizeRelativeToImage({ mySize, mySize });
		Studio::RendererAccessor::GetInstance()->Render(*mySpriteSheet);
	}
}

void Studio::ShopButtonTier2::OnClick()
{
	if (ScoreAccessor::GetInstance()->GetCoinScore() >= myCost)
	{
		if (!myHasBeenPurchased)
		{
			PlayerAccessor::GetInstance()->UpgradeT2(myUpgradeType);
			ScoreAccessor::GetInstance()->RemoveCoinScore(myCost);
			AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);
			mySpriteSheet->GetSprite()->SetColor({ 1,1,1,0.4f });
			myHasBeenPurchased = true;
		}
		
	}
}

void Studio::ShopButtonTier2::Reset()
{
	myHasBeenPurchased = false;
	mySpriteSheet->GetSprite()->SetColor({ 1,1,1,1 });

}

Studio::Enums::Tier2Upgrades Studio::ShopButtonTier2::GetUpgradeType()
{
	return myUpgradeType;
}
