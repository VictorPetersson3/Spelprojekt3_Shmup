#include "stdafx.h"
#include "CoinManager.h"

Studio::CoinManager::CoinManager()
{
	myPlayerCoins = 0;
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
