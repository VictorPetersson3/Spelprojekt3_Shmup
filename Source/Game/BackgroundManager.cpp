#include "stdafx.h"
#include "BackgroundManager.h"
#include "CommonUtilities/CURandom.h"
#include "RendererAccessor.h"
#include "Renderer.h"
#include "BackgroundObject.h"
//#include <iostream>

void Studio::BackgroundManager::CreateTestMapBackground(float LevelWidth)
{
	myLevelWidth = LevelWidth / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x);
	myBackgroundFactory.InitBackGroundObject("sprites/Background/Background_Background_01.dds", 0, "Background");
	myBackgroundFactory.InitBackGroundObject("sprites/Background/Background_MountainRange_TileAble.dds", 1, "Mountains");
	myBackgroundFactory.InitBackGroundObject("sprites/Background/Background_GradientBackground_01.dds", 2, "Gradient");
	myBackgroundFactory.InitBackGroundObject("sprites/Background/Background_CloudTest_01.dds", 3, "Clouds");

	myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject("Background", Tga2D::Vector2f({ 0.5, 0.5 }), 0, Tga2D::Vector2f({ 1.1, 1.1 })));
	
	//Sätt in if statments för dem olika typerna så jag använder rätt överlagring osv
	
	for (int i = 0; i < 10; i++)
	{
		myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject("Mountains", Tga2D::Vector2f({((512.f / static_cast<float>(Tga2D::CEngine::GetInstance()->GetRenderSize().x))) * i, 0.873f }), -0.025f));
	}
	myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject("Gradient", Tga2D::Vector2f({ 0.5, 0.5 }), 0, Tga2D::Vector2f({ 1.1, 1.1 })));

	for (int i = 0; i < 20; i++)
	{
		myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject("Clouds", 
			Tga2D::Vector2f({ CommonUtilities::GetRandomFloat(0, myLevelWidth), CommonUtilities::GetRandomFloat(0.f, 0.6f) }),
			CommonUtilities::GetRandomFloat(0.04f, 0.1f) * (-1.f)));
	}
}

// Lägg till en Temp Object Vector som jag sedan loopar över och kollar layer order och sorterar den baklänges i final versionen av managern

void Studio::BackgroundManager::UpdateBackground(float aDeltaTime)
{
	for (int i = myBackgroundObjects.size(); i-- > 0;)
	{
		myBackgroundObjects.at(i)->Update(aDeltaTime);
		if (myBackgroundObjects.at(i)->GetPosition().x < -0.5)
		{
			myBackgroundObjects.at(i)->SetPosition({ myBackgroundObjects.at(i)->GetPosition().x + myLevelWidth, myBackgroundObjects.at(i)->GetPosition().y });
		}
		Studio::RendererAccessor::GetInstance()->Render(*myBackgroundObjects.at(i));
	}
}

