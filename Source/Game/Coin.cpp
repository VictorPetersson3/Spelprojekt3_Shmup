#include "stdafx.h"
#include "Coin.h"
#include "Timer.h"
#include <tga2d/sprite/sprite.h>

namespace Studio
{
    Coin::Coin(VECTOR2F aSpawnPosition) : GameObject("Sprites/Pickups/coinsprite.dds")
    {
        mySpriteSheet.SetAmountOfFrames({ 8, 1 });
        myPosition = aSpawnPosition;
        mySpriteSheet.SetImagePath("Sprites/Pickups/coinsprite.dds");
        GameObject::myCollider.AddCircleColliderObject({0,0}, 32);
        mySpriteSheet.LoopAnimationInRange(0.1f, { 1,1 }, { 6,1 });
        myScoreValue = 1;
        mySpeed = 100;

        SetGodMode(true);
        myInterval = 1.0f;
        
        myThirdCounter.SetInterval(1.0f);

        myTimeCounter.SetInterval(myInterval);

        myBlinkingCounter.SetInterval(0.1875f);
    }

    void Coin::Update()
    {
        myLifeTime += DELTA_TIME;
        myPosition.x -= DELTA_TIME * mySpeed;
        GameObject::Update(myPosition);

        myThirdCounter.Tick();
        if (myThirdCounter.PastInterval())
        {
            myInterval -= 0.15f;
            myTimeCounter.SetInterval(myInterval);
        }

        myTimeCounter.Tick();
        if (myTimeCounter.PastInterval())
        {
            myTimeCounter.SetInterval(myInterval);
            myIsBlinked = true;
        }

        if (myIsBlinked)
        {
            myBlinkingCounter.Tick();
            if (myBlinkingCounter.PastInterval())
            {
                myIsBlinked = false;
            }
            mySpriteSheet.SetSize({ 64.0f, sinf(myBlinkingCounter.GetTime() * 30.0f) * 8.0f + 64.0f });
        }

        if (myLifeTime >= 7.5f)
        {
            //8.5 - (t(x) - 3.75) * 2
            auto factor = (16.0f - myLifeTime * 2.0f);
            printf_s("Factor: %f\n", factor);
            auto size = 64.0f * factor;
            mySpriteSheet.SetSize({ size, size });
        }
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

