#include "stdafx.h"
#include "GenericButton.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include <iostream>
#include "AudioManagerAccesor.h"
#include "AudioManager.h"
#include "Renderer.h"
#include "RendererAccessor.h"
#include "Timer.h"

#define MOUSEPOS Studio::InputManager::GetInstance()->GetMousePosition()
Studio::GenericButton::GenericButton(const char* aSpritePath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag, int aLayer)
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

	Tga2D::Vector2f spawnPos;
	spawnPos.x = aPosition.x + (static_cast<float>(mySprite->GetImageSize().x) * (aPivot.x - 0.5)) * -1.0f;
	spawnPos.y = aPosition.y + (static_cast<float>(mySprite->GetImageSize().y) * (aPivot.y - 0.5)) * -1.0f;
	myLeft = spawnPos.x - (mySprite->GetImageSize().x * 0.45f);
	myRight = spawnPos.x + (mySprite->GetImageSize().x * 0.45f);
	myTop = spawnPos.y - (mySprite->GetImageSize().y * 0.45f);
	myBottom = spawnPos.y + (mySprite->GetImageSize().y * 0.45f);

	tag = aTag;
	mySize = 1;
	mySizeTimer = 0;
}

Studio::GenericButton::~GenericButton()
{
	delete mySprite;
	delete mySpriteSheet;
	mySprite = nullptr;
	mySpriteSheet = nullptr;
}

void Studio::GenericButton::Update()
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
						AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonMouseOver.flac", false, 0.1f);
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
					mySize = 1; 
					mySizeTimer = 0;
					hasBeenHoveredOver = false;
				}
			}
			else
			{
				hasBeenHoveredOver = false; 
				mySize = 1;
				mySizeTimer = 0;
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

void Studio::GenericButton::OnClick()
{
	AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);
}

bool Studio::GenericButton::IsClicked()
{
	return myIsClicked;
}
