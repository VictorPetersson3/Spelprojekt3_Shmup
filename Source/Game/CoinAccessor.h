#pragma once
#include "CoinManager.h"
namespace Studio
{
    namespace CoinAccessor
    {
        CoinManager* GetInstance();
        void SetInstance(CoinManager* aCoinManager);
    }
}