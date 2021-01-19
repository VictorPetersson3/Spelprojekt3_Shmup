#include "stdafx.h"
#include "TestButton.h"
#include "tga2d/sprite/sprite.h"
#include "InputManager.h"
#include <iostream>

Studio::TestButton::TestButton(const char* aPath, VECTOR2F aPosition, VECTOR2F aSize, VECTOR2F aPivot)
{
	mySprite = new Tga2D::CSprite(aPath);
	mySprite->SetPivot(aPivot);
	mySprite->SetSizeRelativeToImage(aSize);
	mySprite->SetPosition(aPosition);


	myLeft = mySprite->GetPosition().x - (mySprite->GetImageSize().x / 2);
	myRight = mySprite->GetPosition().x + (mySprite->GetImageSize().x / 2);
	myTop = mySprite->GetPosition().y - (mySprite->GetImageSize().y / 2);
	myBottom = mySprite->GetPosition().y + (mySprite->GetImageSize().y / 2);

	myRenderCommand = RenderCommand(mySprite);
}

Studio::TestButton::~TestButton()
{
	delete mySprite;
	mySprite = nullptr;
}

void Studio::TestButton::Update()
{
	if (Studio::InputManager::GetInstance()->GetMousePosition().x >= myLeft && Studio::InputManager::GetInstance()->GetMousePosition().x <= myRight)
	{
		if (Studio::InputManager::GetInstance()->GetMousePosition().y >= myTop && Studio::InputManager::GetInstance()->GetMousePosition().y <= myBottom)
		{
			if (Studio::InputManager::GetInstance()->GetMouseLDown())
			{
				OnClick();
			}
		}
	}
}

void Studio::TestButton::OnClick()
{
	std::cout << "TestButton Pressed" << std::endl;
}

//void Studio::TestButton::Render()
//{
//	RendererAccessor::GetInstance()->RenderRenderCommand(myRenderCommand);
//}
