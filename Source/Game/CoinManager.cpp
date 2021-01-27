#include "stdafx.h"
#include "CoinManager.h"
#include "Coin.h"

Studio::CoinManager::CoinManager()
{
	myPlayerCoins = 0;
}

void Studio::CoinManager::Update()
{
	for (size_t i = 0; i < myWorldCoins.size(); i++)
	{
		myWorldCoins[i]->GetRenderCommand().Render();
	}
}

void Studio::CoinManager::AddCoins(int anAmount)
{
	myPlayerCoins += anAmount;
}

void Studio::CoinManager::RemoveCoins(int anAmount)
{
	myPlayerCoins -= anAmount;

}

void Studio::CoinManager::SetCoins(int anAmount)
{
	myPlayerCoins = anAmount;
}
