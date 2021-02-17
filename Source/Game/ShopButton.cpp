#include "stdafx.h"
#include "ShopButton.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include <iostream>
#include "AudioManagerAccesor.h"
#include "AudioManager.h"
#include <string>
#include "MenuManagerSingleton.h"
#include "MenuManager.h"
#include "MenuObject.h"
#include "TextElement.h"
#include "Timer.h"
#include "ImageElement.h"

#define MOUSEPOS Studio::InputManager::GetInstance()->GetMousePosition()
Studio::ShopButton::ShopButton(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, int aLayer, Enums::Tier1Upgrades aUpgradeType, int aCost, char* aDescription, char* aName)
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

	myLeft = mySpriteSheet->GetPosition().x - (mySprite->GetImageSize().x / 2);
	myRight = mySpriteSheet->GetPosition().x + (mySprite->GetImageSize().x / 2);
	myTop = mySpriteSheet->GetPosition().y - (mySprite->GetImageSize().y / 2);
	myBottom = mySprite->GetPosition().y + (mySprite->GetImageSize().y / 2);

	mySize = 1;
	mySizeTimer = 0;
	CalculateButtonCollider();

}

Studio::ShopButton::~ShopButton()
{
	delete mySprite;
	delete mySpriteSheet;
}

void Studio::ShopButton::Update()
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
						hasBeenHoveredOver = true;
						MenuManagerSingleton::GetInstance()->GetShopDescriptionText()->SetActive(true);
						MenuManagerSingleton::GetInstance()->GetShopDescriptionText()->GetSpriteSheet()->SetImagePath(myDescription);
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

void Studio::ShopButton::OnClick()
{
	if (ScoreAccessor::GetInstance()->GetCoinScore() >= myCost)
	{
		if (!myHasBeenPurchased)
		{
			PlayerAccessor::GetInstance()->UpgradeT1(myUpgradeType);
			AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);
			ScoreAccessor::GetInstance()->RemoveCoinScore(myCost);
			mySpriteSheet->GetSprite()->SetColor({ 1,1,1,0.4f });
			myHasBeenPurchased = true;
		}
	}
}

void Studio::ShopButton::Reset()
{
	mySpriteSheet->GetSprite()->SetColor({ 1,1,1,1 });
	myHasBeenPurchased = false;
}
