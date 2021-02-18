#pragma once
#include "Cutscenes.h"
namespace Studio
{
    namespace CutscenesAccessor
    {
        Cutscenes* GetInstance();
        void SetInstance(Cutscenes*);
    }
}