#include "stdafx.h"
#include "ButtonElement.h"
#include "tga2d\sprite\sprite.h"
#include "InputManager.h"
#include "RendererAccessor.h"
#include "Renderer.h"

Studio::ButtonElement::ButtonElement()
{  
}

Studio::ButtonElement::ButtonElement(const char* aID, const char* aPath, VECTOR2F aPosition, VECTOR2F aSize, VECTOR2F aPivot)
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

    //myId = aID;
}

    Studio::ButtonElement::~ButtonElement()
    {
        delete mySprite;
        mySprite = nullptr;
    }

    bool Studio::ButtonElement::IsClicked()
    {
        if (myIsEnabled == true)
        {
            if (Studio::InputManager::GetInstance()->GetMousePosition().x >= myLeft && Studio::InputManager::GetInstance()->GetMousePosition().x <= myRight)
            {
                if (Studio::InputManager::GetInstance()->GetMousePosition().y >= myTop && Studio::InputManager::GetInstance()->GetMousePosition().x <= myBottom)
                {
                    if (Studio::InputManager::GetInstance()->GetMouseLDown() && myHasBeenClicked == false)
                    {
                        return true;
                        myHasBeenClicked = true;
                    }
                }
            }
        }
        
        return false;
    }

    void Studio::ButtonElement::Render()
    {
        Studio::RendererAccessor::GetInstance()->RenderRenderCommand(myRenderCommand);
    }

    void Studio::ButtonElement::ResetButton()
    {
        myHasBeenClicked = false;
    }



