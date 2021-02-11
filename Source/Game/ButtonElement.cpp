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
	float ratioX = static_cast<float>(Tga2D::CEngine::GetInstance()->GetWindowSize().x) / static_cast<float>(1920);
	float ratioY = static_cast<float>(Tga2D::CEngine::GetInstance()->GetWindowSize().y) / static_cast<float>(1080);
	spawnPos.x = (mySpriteSheet->GetPosition().x + (static_cast<float>(mySprite->GetImageSize().y) * (mySprite->GetPivot().x - 0.5)) * -1.0f) * ratioX;
	spawnPos.y = (mySpriteSheet->GetPosition().y + (static_cast<float>(mySprite->GetImageSize().y) * (mySprite->GetPivot().y - 0.5)) * -1.0f) * ratioY;
	printf("Window Size X: %i Y %i\n", Tga2D::CEngine::GetInstance()->GetWindowSize().x, Tga2D::CEngine::GetInstance()->GetWindowSize().y);
	printf("Render Size X: %i Y %i\n", Tga2D::CEngine::GetInstance()->GetRenderSize().x, Tga2D::CEngine::GetInstance()->GetRenderSize().y);
	printf("Ratio X: %f Y: %f \n\n", ratioX, ratioY);
	float scale;
	if (ratioX > 1)
	{
		scale = 1;
	}
	else
	{
		scale = ratioX * 2;
	}
	myLeft = spawnPos.x - ((mySprite->GetImageSize().x * (0.15f * scale)) * ratioX);
	myRight = spawnPos.x + ((mySprite->GetImageSize().x * (0.15f * scale)) * ratioX);
	myTop = spawnPos.y - ((mySprite->GetImageSize().y * (0.15f * scale)) * ratioX);
	myBottom = spawnPos.y + ((mySprite->GetImageSize().y * (0.15f * scale)) * ratioX);

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
