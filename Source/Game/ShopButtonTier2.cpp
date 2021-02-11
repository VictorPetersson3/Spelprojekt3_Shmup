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

Studio::ShopButtonTier2::ShopButtonTier2(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, int aLayer, Enums::Tier2Upgrades aUpgradeType, int aCost, const char* aDescription)
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

Studio::ShopButtonTier2::~ShopButtonTier2()
{
}

void Studio::ShopButtonTier2::Update()
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
						AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonMouseOver.flac", false, 0.15f);
						hasBeenHoveredOver = true;
						//MenuManagerSingleton::GetInstance()->GetShopDescriptionText()->SetText(myDescription);
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

void Studio::ShopButtonTier2::OnClick()
{
	if (ScoreAccessor::GetInstance()->GetCoinScore() >= myCost)
	{
		if (!myHasBeenPurchased)
		{
			PlayerAccessor::GetInstance()->UpgradeT2(myUpgradeType);
			std::cout << "Shop button pressed" << std::endl;
			ScoreAccessor::GetInstance()->RemoveCoinScore(myCost);
			AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);
			myHasBeenPurchased = true;
		}
		
	}
}

void Studio::ShopButtonTier2::Reset()
{
	myHasBeenPurchased = false;
}
