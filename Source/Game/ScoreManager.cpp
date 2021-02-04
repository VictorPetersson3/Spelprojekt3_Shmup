#include "stdafx.h"
#include "ScoreManager.h"
#include "MenuManagerSingleton.h"
#include <iostream>
#include <string>
namespace Studio
{
	ScoreManager::ScoreManager()
	{
		myCoinScore = 0;
		myKillScore = 0;

		myCoinTextElement = static_cast<TextElement*>(MenuManagerSingleton::GetInstance()->GetHUD()->GetElementWithTag("CoinText"));
		myKillTextElement = static_cast<TextElement*>(MenuManagerSingleton::GetInstance()->GetHUD()->GetElementWithTag("ScoreText"));
		myShopCoinTextElement = static_cast<TextElement*>(MenuManagerSingleton::GetInstance()->GetShop()->GetElementWithTag("ShopCoinText"));
		if (myCoinTextElement != nullptr)
		{
			std::cout << "Score text found" << std::endl;
		}
	}
	void ScoreManager::Update()
	{
		std::string coinScoreString = std::to_string(myCoinScore);
		myCoinTextElement->SetText("x" + coinScoreString);

		std::string killScoreString = std::to_string(myKillScore);
		myKillTextElement->SetText("x" + killScoreString);

		myShopCoinTextElement->SetText("Your score: " + coinScoreString);
	}
	void ScoreManager::AddCoinScore(int anAmount)
	{
		myCoinScore += anAmount;
	}

	void ScoreManager::RemoveCoinScore(int anAmount)
	{
		myCoinScore -= anAmount;
	}

	void ScoreManager::SetCoinScore(int anAmount)
	{
		myCoinScore = anAmount;
	}

	void ScoreManager::AddKillScore(int anAmount)
	{
		myKillScore += anAmount;
	}

	void ScoreManager::RemoveKillScore(int anAmount)
	{
		myKillScore -= anAmount;
	}

	void ScoreManager::SetKillScore(int anAmount)
	{
		myKillScore = anAmount;
	}

	void ScoreManager::ResetScore()
	{
		SetCoinScore(0);
		SetKillScore(0);
	}

	int ScoreManager::GetCoinScore()
	{
		return myCoinScore;
	}

	int ScoreManager::GetKillScore()
	{
		return myKillScore;
	}
}

