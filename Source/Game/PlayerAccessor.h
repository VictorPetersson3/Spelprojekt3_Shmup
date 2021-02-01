#pragma once
#include "Player.h"
namespace Studio
{
    namespace PlayerAccessor
    {
        Player* GetInstance();
        void SetInstance(Player*);
    }
}