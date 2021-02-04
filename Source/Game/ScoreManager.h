#pragma once
#include <vector>
#include "TextElement.h"

namespace Tga2D
{
	class CSprite;
}
namespace Studio
{
	class Score;
	class ScoreManager
	{
	public:
		ScoreManager();
		void Update();
		void AddCoinScore(int anAmount);
		void RemoveCoinScore(int anAmount);
		void SetCoinScore(int anAmount);
		void AddKillScore(int anAmount);
		void RemoveKillScore(int anAmount);
		void SetKillScore(int anAmount);
		void ResetScore();

		int GetCoinScore();
		int GetKillScore();
	private:
		int myCoinScore;
		int myKillScore;

		TextElement* myCoinTextElement;
		TextElement* myKillTextElement;
		TextElement* myShopCoinTextElement;
	};
}


