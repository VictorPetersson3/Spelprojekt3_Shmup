#include "stdafx.h"
#include "LevelAccessor.h"
namespace Studio
{
    namespace LevelAccessor
    {
        namespace
        {
            LevelManager* myInstance;
        }

        LevelManager* GetInstance()
        {
            return myInstance;
        }

        void SetInstance(LevelManager* aLevelManager)
        {
            myInstance = aLevelManager;
        }
    }
}