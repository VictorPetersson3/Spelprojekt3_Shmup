#include "stdafx.h"
#include "StartButton.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include <iostream>
#include "AudioManagerAccesor.h"
#include "AudioManager.h"
#include "LevelAccessor.h"
#include "MenuManager.h"
#include "MenuManagerSingleton.h"
#include "Timer.h"

#include "CutscenesAccessor.h"

#define MOUSEPOS Studio::InputManager::GetInstance()->GetMousePosition()
Studio::StartButton::StartButton(const char* aSpritePath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag,int aLayer,const bool aMainMenuButton)
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

	
	tag = aTag;

	mySize = 1;
	mySizeTimer = 0;
	myScale = aSize;

	myLevelToLoad = 0;
	myIsMainMenuStart = aMainMenuButton;
	CalculateButtonCollider();

}

Studio::StartButton::~StartButton()
{
	delete mySprite;
	delete mySpriteSheet;
	mySprite = nullptr;
	mySpriteSheet = nullptr;
}

void Studio::StartButton::Update()
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


					if (Studio::InputManager::GetInstance()->GetMouseLDown())
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
				mySize = 1;
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

void Studio::StartButton::OnClick()
{
	AudioManagerAccessor::GetInstance()->StopAllSounds();
	if (myIsMainMenuStart)
	{
		CutscenesAccessor::GetInstance()->PlayScene(Enums::Cutscene::Intro);
	}
	else
	{
		myLevelToLoad = LevelAccessor::GetInstance()->GetCurrentLevelIndex();
		if (myLevelToLoad > LevelAccessor::GetInstance()->GetLevelPaths().size() - 1)
		{
			myLevelToLoad = LevelAccessor::GetInstance()->GetCurrentLevelIndex();
		}
		if (myLevelToLoad <= LevelAccessor::GetInstance()->GetLevelPaths().size())
		{
			LevelAccessor::GetInstance()->LoadLevel(myLevelToLoad);
		}
	}

	AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);
	MenuManagerSingleton::GetInstance()->SetIsInShop(false);

	LevelAccessor::GetInstance()->StartUpdating();
}

void Studio::StartButton::SetLevelToLoad(const int aIndex)
{
	myLevelToLoad = aIndex;
}
