#include "stdafx.h"
#include "CoinAccessor.h"
namespace Studio
{
    class CoinManager;
    namespace CoinAccessor
    {
        namespace
        {
            CoinManager* myCoinManager;
        }

        CoinManager* GetInstance()
        {
            return myCoinManager;
        }

        void SetInstance(CoinManager* aCoinManager)
        {
            myCoinManager = aCoinManager;
        }
    }
}