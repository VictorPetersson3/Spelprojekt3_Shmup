#include "stdafx.h"
#include "ReturnToMainMenuButton.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include "RendererAccessor.h"
#include "Renderer.h"
#include "AudioManagerAccesor.h"
#include "AudioManager.h"
#include "MenuManagerSingleton.h"
#include "MenuManager.h"
#include "LevelAccessor.h"
#include "Timer.h"

#define MOUSEPOS Studio::InputManager::GetInstance()->GetMousePosition()
Studio::ReturnToMainMenuButton::ReturnToMainMenuButton(const char* aSpritePath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag, int aLayer)
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

	mySize = 1;
	mySizeTimer = 0;

	CalculateButtonCollider();

	tag = aTag;
}

Studio::ReturnToMainMenuButton::~ReturnToMainMenuButton()
{
	delete mySprite;
	delete mySpriteSheet;
	mySprite = nullptr;
	mySpriteSheet = nullptr;
}

void Studio::ReturnToMainMenuButton::Update()
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
						AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonMouseOver.flac", false, 0.15f);
						hasBeenHoveredOver = true;
					}


					if (Studio::InputManager::GetInstance()->GetMouseLPressed() && myIsClicked == false)
					{
						//OnClick();
						myIsClicked = true;
						//myIsEnabled = false;
					}

					if (myIsClicked && Studio::InputManager::GetInstance()->GetMouseLReleased())
					{
						OnClick();
						myIsClicked = false;
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
			OnClick();
			myIsClicked = false;
		}

		mySpriteSheet->SetSizeRelativeToImage({ mySize, mySize });
		Studio::RendererAccessor::GetInstance()->Render(*mySpriteSheet);
	}
}

void Studio::ReturnToMainMenuButton::OnClick()
{
	AudioManagerAccessor::GetInstance()->StopAllSounds();
	AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonClick.flac", false, 0.15f);
	LevelAccessor::GetInstance()->ClearLevel();
	MenuManagerSingleton::GetInstance()->QuitGameSession();
}
