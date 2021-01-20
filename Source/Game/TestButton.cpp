#include "stdafx.h"
#include "TestButton.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include <iostream>

Studio::TestButton::TestButton()
{

}

Studio::TestButton::TestButton(const char* aPath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot)
{
	mySprite = new Tga2D::CSprite(aPath);
	mySprite->SetPivot(aPivot);
	mySprite->SetSizeRelativeToImage(aSize);
	mySprite->SetPosition(aPosition);


	myLeft = mySprite->GetPosition().x - (mySprite->GetImageSize().x* aSize.x / 2);
	myRight = mySprite->GetPosition().x + (mySprite->GetImageSize().x * aSize.x / 2);
	myTop = mySprite->GetPosition().y - (mySprite->GetImageSize().y * aSize.y / 2);
	myBottom = mySprite->GetPosition().y + (mySprite->GetImageSize().y * aSize.y / 2);

	myRenderCommand = RenderCommand(mySprite, aSize,aPosition);
}

Studio::TestButton::~TestButton()
{
	delete mySprite;
	mySprite = nullptr;
}

void Studio::TestButton::Update()
{
	if (myIsEnabled == true)
	{
		if (myIsClicked == false)
		{
			if (Studio::InputManager::GetInstance()->GetMousePosition().x * renderAspect >= myLeft && Studio::InputManager::GetInstance()->GetMousePosition().x * renderAspect <= myRight)
			{
				if (Studio::InputManager::GetInstance()->GetMousePosition().y * renderAspect >= myTop && Studio::InputManager::GetInstance()->GetMousePosition().y * renderAspect <= myBottom)
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


		Studio::RendererAccessor::GetInstance()->RenderRenderCommand(myRenderCommand);
	}
}

void Studio::TestButton::OnClick()
{
	std::cout << "TestButton Pressed" << std::endl;
}
