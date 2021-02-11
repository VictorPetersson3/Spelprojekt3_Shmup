#include "stdafx.h"
#include "ScoreManager.h"
#include "MenuManagerSingleton.h"
#include <iostream>
#include <string>
#include "AudioManager.h"
#include "AudioManagerAccesor.h"

namespace Studio
{
	ScoreManager::ScoreManager()
	{
		myCoinScore = 0;
		myKillScore = 0;

		myCoinTextElement = static_cast<TextElement*>(MenuManagerSingleton::GetInstance()->GetHUD()->GetElementWithTag("CoinText"));
		myKillTextElement = static_cast<TextElement*>(MenuManagerSingleton::GetInstance()->GetHUD()->GetElementWithTag("ScoreText"));
		myShopCoinTextElement = static_cast<TextElement*>(MenuManagerSingleton::GetInstance()->GetShop()->GetElementWithTag("ShopCoinText"));
	}
	void ScoreManager::Update()
	{
		std::string coinScoreString = std::to_string(myCoinScore);
		myCoinTextElement->SetText("x" + coinScoreString);

		std::string killScoreString = std::to_string(myKillScore);
		myKillTextElement->SetText("x" + killScoreString);

		myShopCoinTextElement->SetText(coinScoreString);
	}
	void ScoreManager::AddCoinScore(int anAmount)
	{
		myCoinScore += anAmount;
		AudioManagerAccessor::GetInstance()->Play2D("Audio/CoinPickUp.mp3", false, 0.2f);
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

