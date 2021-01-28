#include "stdafx.h"
#include "ScoreAccessor.h"
namespace Studio
{
    namespace ScoreAccessor
    {
        namespace
        {
            ScoreManager* myInstance;
        }

        ScoreManager* GetInstance()
        {
            return myInstance;
        }

        void SetInstance(ScoreManager* aMyClass)
        {
            myInstance = aMyClass;
        }
    }
}