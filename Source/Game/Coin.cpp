#include "stdafx.h"
#include "Coin.h"

#define SPRITESHEET GameObject::GetSpriteSheet()

namespace Studio
{
    Coin::Coin(VECTOR2F aSpawnPosition) : GameObject("Sprites/Pickups/coinsprite.dds")
    {
        SPRITESHEET.SetAmountOfFrames({ 8, 1 });
        myPosition = aSpawnPosition;
        mySpriteSheet.SetImagePath("Sprites/Pickups/coinsprite.dds");
        GameObject::myCollider.AddCircleColliderObject({0,0}, 16);
        mySpriteSheet.LoopAnimationInRange(0.1f, { 1,1 }, { 6,1 });
        myScoreValue = 1;
    }


    int Coin::GetScoreValue()
    {
        return myScoreValue;
    }

    VECTOR2F Coin::GetPosition()
    {
        return myPosition;
    }
}

