#include "stdafx.h"
#include "Coin.h"

namespace Studio
{
    Coin::Coin(Tga2D::CSprite* aSprite, VECTOR2F aSpawnPosition) : Coin::GameObject(aSprite)
    {
        mySprite = aSprite;
        myPosition = aSpawnPosition;
        myScoreValue = 1;
    }

    Coin::~Coin()
    {
        SAFE_DELETE(mySprite);
    }

    int Coin::GetScoreValue()
    {
        return myScoreValue;
    }

    RenderCommand& Coin::GetRenderCommand()
    {
        return myRenderCommand;
    }
}

