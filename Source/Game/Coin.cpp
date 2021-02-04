#include "stdafx.h"
#include "Coin.h"
#include "Timer.h"
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
        mySpeed = 100;
    }

    void Coin::Update()
    {
        myLifeTime += Studio::Timer::GetInstance()->TGetDeltaTime();
        myPosition.x += -Studio::Timer::GetInstance()->TGetDeltaTime() * mySpeed;
        GameObject::Update(myPosition);
    }


    int Coin::GetScoreValue()
    {
        return myScoreValue;
    }

    const float Coin::GetLifeTime() const
    {
        return myLifeTime;
    }

    VECTOR2F Coin::GetPosition()
    {
        return myPosition;
    }
}

