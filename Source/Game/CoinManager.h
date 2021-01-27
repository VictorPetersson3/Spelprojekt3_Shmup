#pragma once
#include <vector>
namespace Studio
{
	class Coin;
	class CoinManager
	{
	public:
		CoinManager();
		void Update();
		void AddCoins(int anAmount);
		void RemoveCoins(int anAmount);
		void SetCoins(int anAmount);
	private:
		int myPlayerCoins;
		std::vector<Coin*> myWorldCoins;
	};
}


