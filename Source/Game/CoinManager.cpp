#include "stdafx.h"
#include "CoinManager.h"
#include "Coin.h"
#include "tga2d/sprite/sprite.h"
#include "RendererAccessor.h"
#include "Renderer.h"

namespace Studio
{
	void CoinManager::Update()
	{
		for (int i = myWorldCoins.size(); --i >= 0;)
		{
			myWorldCoins[i]->Update();
			RendererAccessor::GetInstance()->Render(*myWorldCoins[i]);
			if (myWorldCoins[i]->GetLifeTime() > 8.f)
			{
				SAFE_DELETE(myWorldCoins[i]);
				std::swap(myWorldCoins[i], myWorldCoins.back());
				myWorldCoins.pop_back();
			}
		}
	}

	void CoinManager::CreateCoin(VECTOR2F aPosition)
 	{
		myWorldCoins.push_back(new Coin(aPosition));
	}

	void CoinManager::ResetWorldCoins()
	{
		for (int i = 0; i < myWorldCoins.size(); i++)
		{
			SAFE_DELETE(myWorldCoins[i]);
		}
		myWorldCoins.clear();
	}

	std::vector<Coin*>& CoinManager::GetWorldCoins()
	{
		return myWorldCoins;
	}
}


