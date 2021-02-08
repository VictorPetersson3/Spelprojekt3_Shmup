#include "stdafx.h"
#include "LevelSelectButton.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include <iostream>
#include "AudioManagerAccesor.h"
#include "AudioManager.h"
#include "Renderer.h"
#include "RendererAccessor.h"

Studio::LevelSelectButton::LevelSelectButton(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag, const int aLayer)
{
	mySprite = new Tga2D::CSprite(aPath);
	mySprite->SetPivot(aPivot);
	mySprite->SetSizeRelativeToImage(aSize);
	mySprite->SetPosition(aPosition);

	mySpriteSheet = new SpriteSheet(aPath);
	mySpriteSheet->SetPivot(aPivot);
	mySpriteSheet->SetPosition(aPosition);
	mySpriteSheet->SetSizeRelativeToImage(aSize);



	myLeft = mySpriteSheet->GetPosition().x - (mySprite->GetImageSize().x / 2);
	myRight = mySpriteSheet->GetPosition().x + (mySprite->GetImageSize().x / 2);
	myTop = mySpriteSheet->GetPosition().y - (mySprite->GetImageSize().y / 2);
	myBottom = mySprite->GetPosition().y + (mySprite->GetImageSize().y / 2);

	mySpriteSheet->SetLayer(aLayer);

	tag = aTag;
}

Studio::LevelSelectButton::~LevelSelectButton()
{
	delete mySprite;
	delete mySpriteSheet;
	mySprite = nullptr;
	mySpriteSheet = nullptr;
}

void Studio::LevelSelectButton::Update()
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
					if (!hasBeenHoveredOver)
					{
						AudioManagerAccessor::GetInstance()->Play2D("Audio/UI/ButtonHoverTemp.wav", false, 0.05f);
						hasBeenHoveredOver = true;
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

void Studio::LevelSelectButton::OnClick()
{

}
