#pragma once
#include "ScoreManager.h"
namespace Studio
{
    namespace ScoreAccessor
    {
        ScoreManager* GetInstance();
        void SetInstance(ScoreManager*);
    }
}