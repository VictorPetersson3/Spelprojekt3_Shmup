#include "stdafx.h"
#include "SliderElement.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include "AudioManagerAccesor.h"
#include "AudioManager.h"
#include "LevelAccessor.h"
#include "RendererAccessor.h"
#include "Renderer.h"
#include "CommonUtilities/CUMath.h"

#define MOUSEPOS Studio::InputManager::GetInstance()->GetMousePosition()
Studio::SliderElement::SliderElement(const char* aSpritePath, const VECTOR2F& aPosition,const VECTOR2F& aSize, const int aLayer)
{
	mySpriteSheet = new SpriteSheet(aSpritePath);
	mySpriteSheet->GetSprite()->SetColor({ 0.0f, 1.0f, 0.0f, 1.0f });
	mySpriteSheet->SetPivot({ 0.5f,0.5f });
	mySpriteSheet->SetPosition(aPosition);
	mySize = aSize;
	myRatio = 1.f;
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
	ReCalculateColliders();
}

Studio::SliderElement::~SliderElement()
{
	delete mySpriteSheet;
	mySpriteSheet = nullptr;
}

void Studio::SliderElement::Update()
{
	if (myIsEnabled == true)
	{	
		ReCalculateColliders();	
		myHandleSprite->SetPosition({ CommonUtilities::Lerp(myLeft / myRatio, myRight / myRatio, AudioManagerAccessor::GetInstance()->GetVolumeMultiplier()), myHandleSprite->GetPosition().y });
		if (MOUSEPOS.x >= myLeft && MOUSEPOS.x <= myRight)
		{
			if (MOUSEPOS.y >= myTop && MOUSEPOS.y <= myBottom)
			{
					
				if (Studio::InputManager::GetInstance()->GetMouseLDown())
				{
					fillPercentage = (static_cast<float>(MOUSEPOS.x) - myLeft) / (mySize.x * myRatio);
					//Change position to match fill percentage
					myHandleSprite->SetPosition({ static_cast<float>(MOUSEPOS.x) / myRatio, myHandleSprite->GetPosition().y });
				}
			}
		}

		mySpriteSheet->SetSize({ mySize.x * fillPercentage, mySize.y });

		Studio::RendererAccessor::GetInstance()->Render(*myHandleSprite);
		//Get Volume Multiplier
		AudioManagerAccessor::GetInstance()->SetVolumeMultiplier(fillPercentage);
		printf("fillPercentage: %f\n", fillPercentage);
	}

}

void Studio::SliderElement::ReCalculateColliders()
{
	Tga2D::Vector2f spawnPos;
	myRatio = static_cast<float>(Tga2D::CEngine::GetInstance()->GetWindowSize().y) / static_cast<float>(1080.f);
	float EPSILON = 0.00001f;
	float ratioComparison = static_cast<float>(Tga2D::CEngine::GetInstance()->GetWindowSize().x) / static_cast<float>(1920.f);
	if (ratioComparison > myRatio + EPSILON)
	{
		float xSpaceToAdd = (static_cast<float>(Tga2D::CEngine::GetInstance()->GetWindowSize().x) * (ratioComparison - myRatio)) * 0.5;
		xSpaceToAdd = (static_cast<float>(Tga2D::CEngine::GetInstance()->GetWindowSize().x) - (static_cast<float>(Tga2D::CEngine::GetInstance()->GetWindowSize().y) * 1.777777777f)) * 0.5f;
		myLeft = ((mySpriteSheet->GetPosition().x - (mySize.x * 0.5f)) * myRatio) + xSpaceToAdd;
		myRight = ((mySpriteSheet->GetPosition().x + (mySize.x * 0.5f)) * myRatio) + xSpaceToAdd;
	}
	else
	{
		myLeft = (mySpriteSheet->GetPosition().x - (mySize.x * 0.5f)) * myRatio;
		myRight = (mySpriteSheet->GetPosition().x + (mySize.x * 0.5f)) * myRatio;
	}
	myTop = (mySpriteSheet->GetPosition().y - (mySize.y * 0.5f)) * myRatio;
	myBottom = (mySpriteSheet->GetPosition().y + (mySize.y * 0.5f)) * myRatio;
}
