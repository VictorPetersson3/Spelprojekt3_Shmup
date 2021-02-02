#include "stdafx.h"
#include "ShopUI.h"
#include "ShopButton.h"
#include <cstdlib>
#include "CommonUtilities\CURandom.h"
#include "PlayerAccessor.h"
#include "Enums.h"

int Studio::ShopUI::GetRandomNumberInRange(int max)
{
	return CommonUtilities::GetRandomInt(0, max);
}

Studio::ShopUI::ShopUI()
{
		myTier1Buttons.push_back(new ShopButton("Sprites/debugpixel.dds", { 0,0 }, { 128,128 }, { 0.5f,0.5f }, 5000000,Enums::RapidFireUpgrades::AttackSpeedT1,5));
		myTier1Buttons.push_back(new ShopButton("Sprites/debugpixel.dds", { 0,0 }, { 128,128 }, { 0.5f,0.5f }, 5000000, Enums::RapidFireUpgrades::CooldownT1,5));
		myTier1Buttons.push_back(new ShopButton("Sprites/debugpixel.dds", { 0,0 }, { 128,128 }, { 0.5f,0.5f }, 5000000, Enums::RapidFireUpgrades::DurationT1,5));
		myTier1Buttons.push_back(new ShopButton("Sprites/debugpixel.dds", { 0,0 }, { 128,128 }, { 0.5f,0.5f }, 5000000, Enums::RapidFireUpgrades::AttackSpeedT1,5));
		myTier1Buttons.push_back(new ShopButton("Sprites/debugpixel.dds", { 0,0 }, { 128,128 }, { 0.5f,0.5f }, 5000000, Enums::RapidFireUpgrades::CooldownT1,5));
		myTier1Buttons.push_back(new ShopButton("Sprites/debugpixel.dds", { 0,0 }, { 128,128 }, { 0.5f,0.5f }, 5000000, Enums::RapidFireUpgrades::DurationT1,5));

		myTier2Buttons.push_back(new ShopButton("Sprites/debugpixel.dds", { 0,0 }, { 128,128 }, { 0.5f,0.5f }, 500000,Enums::RapidFireUpgrades::AttackSpeedT2,10));
		myTier2Buttons.push_back(new ShopButton("Sprites/debugpixel.dds", { 0,0 }, { 128,128 }, { 0.5f,0.5f }, 500000, Enums::RapidFireUpgrades::DurationT2,10));
		myTier2Buttons.push_back(new ShopButton("Sprites/debugpixel.dds", { 0,0 }, { 128,128 }, { 0.5f,0.5f }, 500000, Enums::RapidFireUpgrades::AttackSpeedT2,10));

		myTier3Buttons.push_back(new ShopButton("Sprites/debugpixel.dds", { 0,0 }, { 128,128 }, { 0.5f,0.5f }, 5000000,Enums::RapidFireUpgrades::PenetratingT3,15));																											  
}

Studio::ShopUI::~ShopUI()
{

}

std::vector<Studio::ShopButton*> Studio::ShopUI::GetShopButtons()
{
	auto myTier1ButtonsTemp = myTier1Buttons;
	auto myTier2ButtonsTemp = myTier2Buttons;

	for (size_t i = 0; i < 6; i++)
	{
		int temp = GetRandomNumberInRange(myTier1ButtonsTemp.size()-1);
		ShopButton* buttonToPushBack = myTier1ButtonsTemp[temp];
		myTier1ButtonsTemp.erase(myTier1ButtonsTemp.begin()+temp);

		switch (i)
		{
		case 0:
			buttonToPushBack->SetPosition({ 960 - 135,200 });
			break;
		case 1:
			buttonToPushBack->SetPosition({ 960,200 });
			break;
		case 2:
			buttonToPushBack->SetPosition({ 960 + 135,200 });
			break;
		case 3:
			buttonToPushBack->SetPosition({ 960 - 135,200+135 });
			break;
		case 4:
			buttonToPushBack->SetPosition({ 960,200 + 135 });
			break;
		case 5:
			buttonToPushBack->SetPosition({ 960 + 135,200 + 135 });
			break;
		default:
			break;
		}

		myActiveButtonPtrs.push_back(buttonToPushBack);
	}

	for (float i = 0; i < 3; i++)
	{		
		int temp = GetRandomNumberInRange(myTier2ButtonsTemp.size()-1);

		ShopButton* buttonToPushBack = myTier2ButtonsTemp[temp];

		myTier2ButtonsTemp.erase(myTier2ButtonsTemp.begin() + temp);

		buttonToPushBack->SetPosition({ 825+i*135, 200 + 135 + 135 });
		

		myActiveButtonPtrs.push_back(buttonToPushBack);
	}

	ShopButton* buttonToPushBack = myTier3Buttons[GetRandomNumberInRange(1)];

	buttonToPushBack->SetPosition({ 960,200 + 135 + 135 + 135 });



	myActiveButtonPtrs.push_back(buttonToPushBack);


	return myActiveButtonPtrs;
}
