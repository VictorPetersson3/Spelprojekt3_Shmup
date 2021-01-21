#include "stdafx.h"
#include "Score.h"
#include "tga2d/text/text.h"
#include <iostream>
namespace Studio
{
	Score::Score()
	{
		myScore = 0;
		//SAFE_CREATE(myScoreText, Tga2D::CText("Text/arial.ttf", Tga2D::EFontSize_18));
		//
		//myScoreText->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		//myScoreText->SetPosition({ 0.1f, 0.08f });

		myTextElement = static_cast<TextElement*>(MenuManagerSingleton::GetInstance()->GetMainMenu()->GetElementWithTag("ScoreText"));
		if (myTextElement != nullptr)
		{
			std::cout << "Score text found" << std::endl;
		}

	}
	Score::~Score()
	{
		SAFE_DELETE(myScoreText);
	}
	void Score::Update()
	{
		std::string s = std::to_string(myScore);
		//myScoreText->SetText("SCORE: " + s);
		myTextElement->SetText("SCORE: " + s);
	}
	void Score::Render()
	{
		myScoreText->Render();
	}
	void Score::AddToScore(int aValue)
	{
		myScore += aValue;
	}
	void Score::SetScore(int aValue)
	{
		myScore = aValue;
	}
}
