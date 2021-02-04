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
		void Update();
		void CreateCoin(VECTOR2F aPosition);
		void ResetWorldCoins();
		std::vector<Coin*> &GetWorldCoins();
	private:
		std::vector<Coin*> myWorldCoins;
	};
}


