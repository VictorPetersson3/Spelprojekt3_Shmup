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

Studio::StartButton::StartButton(const char* aSpritePath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag,int aLayer,const bool aShouldStartnextLevel)
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

	myLeft = mySpriteSheet->GetPosition().x - (mySprite->GetImageSize().x / 2);
	myRight = mySpriteSheet->GetPosition().x + (mySprite->GetImageSize().x / 2);
	myTop = mySpriteSheet->GetPosition().y - (mySprite->GetImageSize().y / 2);
	myBottom = mySprite->GetPosition().y + (mySprite->GetImageSize().y / 2);

	tag = aTag;

	myShouldLoadNextLevel = aShouldStartnextLevel;
	myLevelToLoad = 0;
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
					hasBeenHoveredOver = false;
					AudioManagerAccessor::GetInstance()->StopSound("Audio/ButtonMouseOver.wav");
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

void Studio::StartButton::OnClick()
{
	if (myShouldLoadNextLevel)
	{
		myLevelToLoad = LevelAccessor::GetInstance()->GetCurrentLevelIndex() + 1;

		if (myLevelToLoad >= LevelAccessor::GetInstance()->GetLevelPaths().size() -1)
		{
			myLevelToLoad = LevelAccessor::GetInstance()->GetCurrentLevelIndex();
		}
		if (myLevelToLoad <= LevelAccessor::GetInstance()->GetLevelPaths().size())
		{
			LevelAccessor::GetInstance()->LoadLevel(myLevelToLoad);
		}
	}
	else
	{
		if (myLevelToLoad <= LevelAccessor::GetInstance()->GetLevelPaths().size())
		{
			LevelAccessor::GetInstance()->LoadLevel(myLevelToLoad);
		}
	}

	

	AudioManagerAccessor::GetInstance()->StopAllSounds();
	AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);
	AudioManagerAccessor::GetInstance()->Play2D("Audio/PiratesOfTheBalticLevel12Song.mp3", true, 0.17f);

	//AudioManagerAccessor::GetInstance()->Play2D("Audio/MainTheme.mp3", true, 0.15f);

	//MenuManagerSingleton::GetInstance()->GetShopDescriptionText()->SetActive(false);

	printf("I have started level: %f", myLevelToLoad);
	LevelAccessor::GetInstance()->StartUpdating();
}

void Studio::StartButton::SetLevelToLoad(const int aIndex)
{
	myLevelToLoad = aIndex;
}
