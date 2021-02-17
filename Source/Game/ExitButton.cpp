#include "stdafx.h"
#include "ExitButton.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include <iostream>
#include "AudioManagerAccesor.h"
#include "AudioManager.h"
#include "Renderer.h"
#include "RendererAccessor.h"
#include <stdlib.h>
#include "Timer.h"

#define MOUSEPOS Studio::InputManager::GetInstance()->GetMousePosition()
Studio::ExitButton::ExitButton(const char* aSpritePath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag, int aLayer)
{
	mySprite = new Tga2D::CSprite(aSpritePath);
	mySprite->SetPivot(aPivot);
	mySprite->SetSizeRelativeToImage(aSize);
	mySprite->SetPosition(aPosition);

	mySpriteSheet = new SpriteSheet(aSpritePath);
	mySpriteSheet->SetPivot(aPivot);
	mySpriteSheet->SetPosition(aPosition);
	mySpriteSheet->SetSizeRelativeToImage(aSize);
	mySpriteSheet->SetLayer(aLayer);

	mySize = aSize.x;
	myOriginalSize = aSize.x;
	mySizeTimer = 0;

	CalculateButtonCollider();

	tag = aTag;
}

Studio::ExitButton::~ExitButton()
{
	delete mySprite;
	delete mySpriteSheet;
	mySprite = nullptr;
	mySpriteSheet = nullptr;
}

void Studio::ExitButton::Update()
{

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
						AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonMouseOver.flac", false, 0.05f);
						hasBeenHoveredOver = true;
					}


					if (Studio::InputManager::GetInstance()->GetMouseLPressed())
					{
						OnClick();
						myIsClicked = true;
						myIsEnabled = false;
					}
				}
				else
				{
					mySize = myOriginalSize;
					mySizeTimer = 0;
					hasBeenHoveredOver = false;
				}
			}
			else
			{
				mySize = myOriginalSize;
				mySizeTimer = 0;
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

void Studio::ExitButton::OnClick()
{
	PostMessage(myWindowHandle, WM_CLOSE, 0, 0);
	AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);

}
