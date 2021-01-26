#pragma once
namespace Studio
{
	class CoinManager
	{
	public:
		CoinManager();
		void AddCoins(int anAmount);
		void RemoveCoins(int anAmount);
		void SetCoins(int anAmount);
	private:
		int myPlayerCoins;
	};
}


