#include "stdafx.h"
#include "PlayerAccessor.h"
namespace Studio
{
    namespace PlayerAccessor
    {
        namespace
        {
            Player* myInstance;
        }

        Player* GetInstance()
        {
            return myInstance;
        }

        void SetInstance(Player* aMyClass)
        {
            myInstance = aMyClass;
        }
    }
}