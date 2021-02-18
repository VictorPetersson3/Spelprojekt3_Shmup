#include "stdafx.h"
#include "CutscenesAccessor.h"
namespace Studio
{
    namespace CutscenesAccessor
    {
        namespace
        {
            Cutscenes* myInstance;
        }

        Cutscenes* GetInstance()
        {
            return myInstance;
        }

        void SetInstance(Cutscenes* aCutscenes)
        {
            myInstance = aCutscenes;
        }
    }
}