#include "stdafx.h"
#include "ButtonElement.h"
#include <iostream>
#include "tga2d/sprite/sprite.h"

Studio::ButtonElement::ButtonElement()
{
	myBottom = 0;
	myTop = 0;
	myLeft = 0;
	myRight = 0;

	mySprite = nullptr;
}

Studio::ButtonElement::~ButtonElement()
{

}

void Studio::ButtonElement::CalculateButtonCollider()
{
	Tga2D::Vector2f spawnPos;
	float ratio = static_cast<float>(Tga2D::CEngine::GetInstance()->GetWindowSize().x) / static_cast<float>(1920);

	spawnPos.x = (mySpriteSheet->GetPosition().x + (static_cast<float>(mySprite->GetImageSize().y) * (mySprite->GetPivot().x - 0.5)) ) * ratio;
	spawnPos.y = (mySpriteSheet->GetPosition().y + (static_cast<float>(mySprite->GetImageSize().y) * (mySprite->GetPivot().y - 0.5)) ) * ratio;
	//printf("Window Size X: %i Y %i\n", Tga2D::CEngine::GetInstance()->GetWindowSize().x, Tga2D::CEngine::GetInstance()->GetWindowSize().y);
	
	myLeft = spawnPos.x - (mySprite->GetImageSize().x * (0.35f * ratio));
	myRight = spawnPos.x + (mySprite->GetImageSize().x * (0.35f * ratio));
	myTop = spawnPos.y - (mySprite->GetImageSize().y * (0.35f * ratio));
	myBottom = spawnPos.y + (mySprite->GetImageSize().y * (0.35f * ratio));
}

void Studio::ButtonElement::OnClick()
{

}

void Studio::ButtonElement::Update()
{
		
}

void Studio::ButtonElement::SetPosition(VECTOR2F aPosition)
{
	mySpriteSheet->SetPosition(aPosition);
}
