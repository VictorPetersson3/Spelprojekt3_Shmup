#pragma once
#include "LevelManager.h"
namespace Studio
{
    namespace LevelAccessor
    {
        LevelManager* GetInstance();
        void SetInstance(LevelManager*);
    }
}

