#pragma once
#include <vector>

namespace Tga2D
{
	class CSprite;
}
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
		void CreateCoin(VECTOR2F aPosition);

		std::vector<Coin*> &GetWorldCoins();
	private:
		int myPlayerCoins;
		std::vector<Coin*> myWorldCoins;
	};
}


