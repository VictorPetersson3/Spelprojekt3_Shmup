#include "stdafx.h"
#include "BackgroundManager.h"
#include "CommonUtilities/CURandom.h"
#include "RendererAccessor.h"
#include "Renderer.h"
#include "BackgroundObject.h"
#include <iostream>

void Studio::BackgroundManager::CreateTestMapBackground(float LevelWidth)
{
	myLevelWidth = LevelWidth;
	myBackgroundFactory.InitBackGroundObject("sprites/Background/Background_Background_01.dds", 0, "Background");
	myBackgroundFactory.InitBackGroundObject("sprites/Background/Background_MountainRange_TileAble.dds", 1, "Mountains");
	myBackgroundFactory.InitBackGroundObject("sprites/Background/Background_GradientBackground_01.dds", 2, "Gradient");
	myBackgroundFactory.InitBackGroundObject("sprites/Background/Background_CloudTest_01.dds", 3, "Clouds");

	myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject("Background", Tga2D::Vector2f({ 960, 540 }), 0, Tga2D::Vector2f({ 1.1, 1.1 })));
	
	//Sätt in if statments för dem olika typerna så jag använder rätt överlagring osv
	
	for (int i = 0; i < 10; i++)
	{
		myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject("Mountains", Tga2D::Vector2f({512.f * i, 943.f}), -50.0f));
		std::cout << "Mountain X: " << 512.f * i << std::endl;
	}
	myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject("Gradient", Tga2D::Vector2f({ 960, 540 }), 0, Tga2D::Vector2f({ 1.1, 1.1 })));

	for (int i = 0; i < 20; i++)
	{
		myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject("Clouds", 
			Tga2D::Vector2f({ CommonUtilities::GetRandomFloat(0, myLevelWidth), CommonUtilities::GetRandomFloat(0.f, 600.f) }),
			CommonUtilities::GetRandomFloat(-100.f, -20.f) )); 
	}
}

// Lägg till en Temp Object Vector som jag sedan loopar över och kollar layer order och sorterar den baklänges i final versionen av managern

void Studio::BackgroundManager::UpdateBackground(float aDeltaTime)
{
	for (int i = 0; i < myBackgroundObjects.size(); i++)
	{
		myBackgroundObjects.at(i)->Update(aDeltaTime);
		if (myBackgroundObjects.at(i)->GetPosition().x < -513.f)
		{
			myBackgroundObjects.at(i)->SetPosition({ myBackgroundObjects.at(i)->GetPosition().x + myLevelWidth, myBackgroundObjects.at(i)->GetPosition().y });
		}
		Studio::RendererAccessor::GetInstance()->Render(*myBackgroundObjects.at(i));
	}
}

