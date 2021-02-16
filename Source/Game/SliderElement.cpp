#include "stdafx.h"
#include "SliderElement.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include <iostream>
#include "AudioManagerAccesor.h"
#include "AudioManager.h"
#include "LevelAccessor.h"
#include "RendererAccessor.h"
#include "Renderer.h"

Studio::SliderElement::SliderElement(const char* aSpritePath, const VECTOR2F& aPosition,const VECTOR2F& aSize, const int aLayer)
{
	mySpriteSheet = new SpriteSheet(aSpritePath);
	mySpriteSheet->GetSprite()->SetColor({ 0.0f, 1.0f, 0.0f, 1.0f });
	mySpriteSheet->SetPivot({ 0.5f,0.5f });
	mySpriteSheet->SetPosition(aPosition);
	mySize = aSize;

	myLeft = mySpriteSheet->GetPosition().x;
	myRight = mySpriteSheet->GetPosition().x + (mySize.x);
	myTop = mySpriteSheet->GetPosition().y - (mySize.y / 2);
	myBottom = mySpriteSheet->GetPosition().y + (mySize.y / 2);

	mySpriteSheet->SetPivot({ 0.0f,0.5f });
	mySpriteSheet->SetLayer(aLayer);

	myHandleSprite = new SpriteSheet("Sprites/UI/UI_volumeSlider.dds");
	myHandleSprite->SetPivot({ 0.5f,0.5f });
	myHandleSprite->SetPosition({ mySpriteSheet->GetPosition().x + (mySize.x),mySpriteSheet->GetPosition().y });

	myHandleSprite->SetLayer(100);

	std::cout << myLeft << "" << myRight << std::endl;
}

Studio::SliderElement::~SliderElement()
{
	delete mySpriteSheet;
	mySpriteSheet = nullptr;
}

void Studio::SliderElement::Update()
{

	myWindowHandle = GetForegroundWindow();

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(myWindowHandle, &pt);


	if (myIsEnabled == true)
	{	
			if (pt.x >= myLeft && pt.x <= myRight)
			{
				if (pt.y >= myTop && pt.y <= myBottom)
				{
					
					if (Studio::InputManager::GetInstance()->GetMouseLDown())
					{
						fillPercentage = (pt.x - myLeft) / mySize.x;
						myHandleSprite->SetPosition({ static_cast<float>(pt.x),myHandleSprite->GetPosition().y });
					}
				}
			}

		mySpriteSheet->SetSize({ mySize.x * fillPercentage,mySize.y });
		//myHandleSprite->SetPosition({ myRight,myHandleSprite->GetPosition().y });

		Studio::RendererAccessor::GetInstance()->Render(*myHandleSprite);
		//Studio::RendererAccessor::GetInstance()->Render(*mySpriteSheet);
		AudioManagerAccessor::GetInstance()->SetVolumeMultiplier(fillPercentage);
	}

}
