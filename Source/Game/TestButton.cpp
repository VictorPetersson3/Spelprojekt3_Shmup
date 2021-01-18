#include "stdafx.h"
#include "TestButton.h"
#include "tga2d\sprite\sprite.h"

#include <iostream>

Studio::TestButton::TestButton(const char* aID, const char* aPath, VECTOR2F aPosition, VECTOR2F aSize, VECTOR2F aPivot)
{
    mySprite = new Tga2D::CSprite(aPath);

    mySprite->SetPivot(aPivot);
    mySprite->SetPosition(aPosition);
    mySprite->SetSizeRelativeToImage(aSize);


    myLeft = mySprite->GetPosition().x - (mySprite->GetSize().x / 2);
    myRight = mySprite->GetPosition().x + (mySprite->GetSize().x / 2);
    myTop = mySprite->GetPosition().y - (mySprite->GetSize().y / 2);
    myBottom = mySprite->GetPosition().y + (mySprite->GetSize().y / 2);

    myRenderCommand = RenderCommand(mySprite);

    myId = aID;
}

void Studio::TestButton::OnClick()
{
	std::cout << "GUI Button pressed" << std::endl;
}
