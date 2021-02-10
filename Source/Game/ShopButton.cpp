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

Studio::ShopButton::ShopButton(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, int aLayer, Enums::Tier1Upgrades aUpgradeType, int aCost, const char* aDescription)
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

	myLeft = mySpriteSheet->GetPosition().x - (mySprite->GetImageSize().x / 2);
	myRight = mySpriteSheet->GetPosition().x + (mySprite->GetImageSize().x / 2);
	myTop = mySpriteSheet->GetPosition().y - (mySprite->GetImageSize().y / 2);
	myBottom = mySprite->GetPosition().y + (mySprite->GetImageSize().y / 2);

}

Studio::ShopButton::~ShopButton()
{
}

void Studio::ShopButton::Update()
{

	myLeft = mySpriteSheet->GetPosition().x - (128 / 2);
	myRight = mySpriteSheet->GetPosition().x + (128 / 2);
	myTop = mySpriteSheet->GetPosition().y - (128 / 2);
	myBottom = mySpriteSheet->GetPosition().y + (128 / 2);


	if (myIsEnabled == true)
	{

		myWindowHandle = GetForegroundWindow();

		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(myWindowHandle, &pt);

		
		if (myIsClicked == false)
		{
			if (pt.x >= myLeft && pt.x <= myRight)
			{
				if (pt.y >= myTop && pt.y <= myBottom)
				{
					if (!hasBeenHoveredOver)
					{
						AudioManagerAccessor::GetInstance()->Play2D("Audio/UI/ButtonHoverTemp.wav", false, 0.05f);
						hasBeenHoveredOver = true;
						MenuManagerSingleton::GetInstance()->GetShopDescriptionText()->SetText(myDescription);
					}

					if (Studio::InputManager::GetInstance()->GetMouseLPressed())
					{
						OnClick();
						myIsClicked = true;
					}
				}
				else
				{
					hasBeenHoveredOver = false;
				}
			}
			else
			{
				hasBeenHoveredOver = false;
			}
		}

		if (Studio::InputManager::GetInstance()->GetMouseLReleased() && myIsClicked)
		{
			myIsClicked = false;
		}

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
			std::cout << "Shop button pressed" << std::endl;
			ScoreAccessor::GetInstance()->RemoveCoinScore(myCost);
			myHasBeenPurchased = true;
		}
	}
}

void Studio::ShopButton::Reset()
{
	myHasBeenPurchased = false;
}

//void Studio::ShopButton::SetPosition(VECTOR2F aPosition)
//{
//	mySpriteSheet->SetPosition(aPosition);
//}
//