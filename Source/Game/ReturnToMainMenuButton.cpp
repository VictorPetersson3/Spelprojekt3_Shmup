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
						AudioManagerAccessor::GetInstance()->Play2D("Audio/ButtonMouseOver.mp3", false, 0.05f);
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

void Studio::ReturnToMainMenuButton::OnClick()
{
	MenuManagerSingleton::GetInstance()->QuitGameSession();
	LevelAccessor::GetInstance()->ClearLevel();
}
