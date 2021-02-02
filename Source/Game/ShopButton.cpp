#include "stdafx.h"
#include "ShopButton.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include <iostream>
#include "AudioManagerAccesor.h"
#include "AudioManager.h"

Studio::ShopButton::ShopButton(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, int aLayer)
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
	if (myIsEnabled == true)
	{

		myWindowHandle = GetForegroundWindow();

		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(myWindowHandle, &pt);


		if (myIsEnabled == true)
		{
			if (myIsClicked == false)
			{
				if (pt.x >= myLeft && pt.x <= myRight)
				{
					if (pt.y >= myTop && pt.y <= myBottom)
					{
						if (Studio::InputManager::GetInstance()->GetMouseLPressed())
						{
							OnClick();
							myIsClicked = true;
							myIsEnabled = false;
						}
					}
				}
			}

			if (Studio::InputManager::GetInstance()->GetMouseLReleased() && myIsClicked)
			{
				myIsClicked = false;
			}

			Studio::RendererAccessor::GetInstance()->Render(*mySpriteSheet);

		}
	}
}

void Studio::ShopButton::OnClick()
{

}

//void Studio::ShopButton::SetPosition(VECTOR2F aPosition)
//{
//	mySpriteSheet->SetPosition(aPosition);
//}
//