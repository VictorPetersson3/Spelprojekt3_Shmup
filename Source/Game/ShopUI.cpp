#include "stdafx.h"
#include "ShopUI.h"
#include "ShopButton.h"
#include <cstdlib>
#include "CommonUtilities\CURandom.h"
#include "PlayerAccessor.h"
#include "Enums.h"
#include <string>

int Studio::ShopUI::GetRandomNumberInRange(int max)
{
	return CommonUtilities::RandNumbInRange(0, max);
}

Studio::ShopUI::ShopUI()
{

	myTier1Buttons.push_back(new ShopButton("Sprites/UI/ShopUI/FinalCards/shopUI_cards_AdrenalineRush_Tier1.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier1Upgrades::RapidFireAttackSpeed, 10, "Sprites/UI/ShopUI/RapidFireAST1.dds", "Adrenaline Rush Tier 1"));
	myTier1Buttons.push_back(new ShopButton("Sprites/UI/ShopUI/FinalCards/shopUI_cards_DrumMagazine_Tier1.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier1Upgrades::RapidFireDuration, 10, "Sprites/UI/ShopUI/RapidFireDUT1.dds", "Drum Magazine Tier 1"));
	myTier1Buttons.push_back(new ShopButton("Sprites/UI/ShopUI/FinalCards/shopUI_cards_RapidReload_Tier1.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier1Upgrades::RapidFireCooldown, 10, "Sprites/UI/ShopUI/RapidFireCDT1.dds", "Rapid Reload Tier 1"));
	myTier1Buttons.push_back(new ShopButton("Sprites/UI/ShopUI/FinalCards/shopUI_cards_ExtendedChargerCable_Tier1.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier1Upgrades::ShieldCooldown, 10, "Sprites/UI/ShopUI/ShieldCDT1.dds", "Extended Charger Cable Tier 1"));
	myTier1Buttons.push_back(new ShopButton("Sprites/UI/ShopUI/FinalCards/shopUI_cards_StormReaktor_Tier1.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier1Upgrades::ShieldDuration, 10, "Sprites/UI/ShopUI/ShieldDUT1.dds","Storm Reaktor Tier 1"));
	myTier1Buttons.push_back(new ShopButton("Sprites/UI/ShopUI/FinalCards/shopUI_cards_5T0NK5BatteryCore_Tier1.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier1Upgrades::ShieldHealth, 10, "Sprites/UI/ShopUI/ShieldHPT1.dds","5TONK% Battery Core Tier 1"));
	myTier1Buttons.push_back(new ShopButton("Sprites/UI/ShopUI/FinalCards/shopUI_cards_Triggerhappy_Tier1.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier1Upgrades::BasicAttackSpeed, 10, "Sprites/UI/ShopUI/BasicAttackSpeedT1.dds","Trigger Happy Tier 1"));
	myTier1Buttons.push_back(new ShopButton("Sprites/UI/ShopUI/FinalCards/shopUI_cards_ArkReaktor_Tier1.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier1Upgrades::MissileCooldown, 10, "Sprites/UI/ShopUI/MissileCDRT1.dds","Ark Reaktor Tier 1"));
	myTier1Buttons.push_back(new ShopButton("Sprites/UI/ShopUI/FinalCards/shopUI_cards_GrannysDoughRecipe_Tier1.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier1Upgrades::MissileDamage, 10, "Sprites/UI/ShopUI/MissileDMGT1.dds","Grannys Dough Recipe Tier 1"));
	myTier1Buttons.push_back(new ShopButton("Sprites/UI/ShopUI/FinalCards/shopUI_cards_BluesprintEnlarger_Tier1.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier1Upgrades::MissileExplosionRadius, 10, "Sprites/UI/ShopUI/MissileRADT1.dds","Bluesprint Enlarger Tier 1"));
	
	myTier2Buttons.push_back(new ShopButtonTier2("Sprites/UI/ShopUI/FinalCards/shopUI_cards_AndAnotherOne_Tier2.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier2Upgrades::BasicAttackAdditionalProjectile, 20, "Sprites/UI/ShopUI/BasicAttackPlusOneT2.dds","And Another One"));
	myTier2Buttons.push_back(new ShopButtonTier2("Sprites/UI/ShopUI/FinalCards/shopUI_cards_DrumMagazine_Tier2.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier2Upgrades::RapidFireDuration, 20, "Sprites/UI/ShopUI/RapidFireDUT2.dds","Drum Magazine Tier 2"));
	myTier2Buttons.push_back(new ShopButtonTier2("Sprites/UI/ShopUI/FinalCards/shopUI_cards_ExtendedChargerCable_Tier2.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier2Upgrades::ShieldCooldown, 20, "Sprites/UI/ShopUI/ShieldCDT2.dds", "Extended Charger Cable Tier 2"));
	myTier2Buttons.push_back(new ShopButtonTier2("Sprites/UI/ShopUI/FinalCards/shopUI_cards_Triggerhappy_Tier2.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier2Upgrades::BasicAttackSpeed, 20, "Sprites/UI/ShopUI/BasicAttackSpeedT2.dds","Trigger Happy Tier 2"));
	myTier2Buttons.push_back(new ShopButtonTier2("Sprites/UI/ShopUI/FinalCards/shopUI_cards_ArkReaktor_Tier2.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier2Upgrades::MissileCooldown, 20, "Sprites/UI/ShopUI/MissileCDRT2.dds","Ark Reaktor Tier 2"));
	myTier2Buttons.push_back(new ShopButtonTier2("Sprites/UI/ShopUI/FinalCards/shopUI_cards_GrannysDoughRecipe_Tier2.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier2Upgrades::MissileDamage, 20, "Sprites/UI/ShopUI/MissileDMGT2.dds","Grannys Dough Recipe Tier 2"));
	myTier2Buttons.push_back(new ShopButtonTier2("Sprites/UI/ShopUI/FinalCards/shopUI_cards_BluesprintEnlarger_Tier2.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier2Upgrades::MissileExplosionRadius, 20, "Sprites/UI/ShopUI/MissileRADT2.dds", "Bluesprint Enlarger Tier 2"));
	myTier2Buttons.push_back(new ShopButtonTier2("Sprites/UI/ShopUI/FinalCards/shopUI_cards_AdrenalineRush_Tier2.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier2Upgrades::RapidFireAttackSpeed, 20, "Sprites/UI/ShopUI/RapidFireAST2.dds","Adrenaline Rush Tier 2"));
	myTier2Buttons.push_back(new ShopButtonTier2("Sprites/UI/ShopUI/FinalCards/shopUI_cards_StormReaktor_Tier2.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier2Upgrades::ShieldDuration, 20, "Sprites/UI/ShopUI/ShieldDUT2.dds","Storm Reaktor Tier 2"));
	myTier2Buttons.push_back(new ShopButtonTier2("Sprites/UI/ShopUI/FinalCards/shopUI_cards_5T0NK5BatteryCore_Tier2.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier2Upgrades::ShieldHealth, 20, "Sprites/UI/ShopUI/ShieldHPT2.dds","5TONK% Battery Core Tier 2"));
	

	myTier3Buttons.push_back(new ShopButtonTier3("Sprites/UI/ShopUI/FinalCards/shopUI_cards_Triggerhappy_Tier3.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier3Upgrades::BasicAttackSpeed, 30, "Sprites/UI/ShopUI/BasicAttackSpeedT3.dds","Trigger Happy Tier 3"));
	myTier3Buttons.push_back(new ShopButtonTier3("Sprites/UI/ShopUI/FinalCards/shopUI_cards_G3TR3-KT_Tier3.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier3Upgrades::MissileCluster, 30, "Sprites/UI/ShopUI/MissileT3.dds", "G3TR3-KT"));
	myTier3Buttons.push_back(new ShopButtonTier3("Sprites/UI/ShopUI/FinalCards/shopUI_cards_RideTheLightning_Tier3.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier3Upgrades::RapidFirePenetrating, 30, "Sprites/UI/ShopUI/RapidFirePENT3.dds","Ride The Lightning"));
	myTier3Buttons.push_back(new ShopButtonTier3("Sprites/UI/ShopUI/FinalCards/shopUI_cards_EMPoweredShieldReactor_Tier3.dds", { 0,0 }, { 1,1 }, { 0.5f,0.5f }, 500, Enums::Tier3Upgrades::ShieldExplosion, 30, "Sprites/UI/ShopUI/ShieldT3.dds","EMPowered Shield Reactor"));

}

Studio::ShopUI::~ShopUI()
{
	for (ShopButton* s : myTier1Buttons)
	{
		SAFE_DELETE(s);


	}

	for (ShopButtonTier2* s : myTier2Buttons)
	{
		SAFE_DELETE(s);

	}

	for (ShopButtonTier3* s : myTier3Buttons)
	{
		SAFE_DELETE(s);
	}

	myTier1Buttons.clear();
	myTier2Buttons.clear();
	myTier3Buttons.clear();
}

void Studio::ShopUI::ResetButtons()
{
	for (ShopButton* b : myTier1Buttons)
	{
		b->Reset();
	}
	for (ShopButtonTier2* p : myTier2Buttons)
	{
		p->Reset();
	}
}

std::vector<Studio::ButtonElement*> Studio::ShopUI::GetShopButtons()
{
	myActiveButtonPtrs.clear();

	auto myTier1ButtonsTemp = myTier1Buttons;
	auto myTier2ButtonsTemp = myTier2Buttons;
	auto myTier3ButtonsTemp = myTier3Buttons;

	for (size_t i = 0; i < 6; i++)
	{
		int temp = GetRandomNumberInRange(myTier1ButtonsTemp.size()-1);
		ShopButton* buttonToPushBack = myTier1ButtonsTemp[temp];
		myTier1ButtonsTemp.erase(myTier1ButtonsTemp.begin()+temp);

		switch (i)
		{
		case 0:
			buttonToPushBack->SetPosition({ 420, 440 });
			break;								
		case 1:									 
			buttonToPushBack->SetPosition({ 570, 440 });
			break;								
		case 2:									 
			buttonToPushBack->SetPosition({ 720, 440 });
			break;								 
		case 3:									
			buttonToPushBack->SetPosition({ 870, 440 });
			break;
		case 4:
			buttonToPushBack->SetPosition({ 1020, 440 });
			break;
		case 5:
			buttonToPushBack->SetPosition({ 420, 600  });
			break;
		default:
			break;
		}

		myActiveButtonPtrs.push_back(buttonToPushBack);
	}

	for (float i = 0; i < 3; i++)
	{		
		int temp = GetRandomNumberInRange(myTier2ButtonsTemp.size()-1);

		ShopButtonTier2* buttonToPushBack = myTier2ButtonsTemp[temp];

		if (PlayerAccessor::GetInstance()->GetAmountOfProjectiles() >= 3 && buttonToPushBack->GetUpgradeType() == Enums::Tier2Upgrades::BasicAttackAdditionalProjectile)
		{
			myTier2ButtonsTemp.erase(myTier2ButtonsTemp.begin() + temp);
			temp = GetRandomNumberInRange(myTier2ButtonsTemp.size() - 1);
			buttonToPushBack = myTier2ButtonsTemp[temp];
		}

		myTier2ButtonsTemp.erase(myTier2ButtonsTemp.begin() + temp);

		buttonToPushBack->SetPosition({ 570+i*150, 600 });

		myActiveButtonPtrs.push_back(buttonToPushBack);
	}

	
	

	ShopButtonTier3* buttonToPushBack = myTier3Buttons[GetRandomNumberInRange(myTier3Buttons.size() - 1)];

	if (PlayerAccessor::GetInstance() != nullptr)
	{
		if (PlayerAccessor::GetInstance()->GetHasClusterBombs())
		{
			while (buttonToPushBack->GetUpgradeType() == Enums::Tier3Upgrades::MissileCluster)
			{
				int temp = GetRandomNumberInRange(myTier3Buttons.size() - 1);
				buttonToPushBack = myTier3Buttons[temp];
			}

		}
		if (PlayerAccessor::GetInstance()->GetHasExplodingShield())
		{
			while (buttonToPushBack->GetUpgradeType() == Enums::Tier3Upgrades::ShieldExplosion)
			{
				int temp = GetRandomNumberInRange(myTier3Buttons.size() - 1);
				buttonToPushBack = myTier3Buttons[temp];
			}
		}
		if (PlayerAccessor::GetInstance()->GetHasPenetratingRounds())
		{
			while (buttonToPushBack->GetUpgradeType() == Enums::Tier3Upgrades::RapidFirePenetrating)
			{
				int temp = GetRandomNumberInRange(myTier3Buttons.size() - 1);
				buttonToPushBack = myTier3Buttons[temp];
			}
		}
	}

	buttonToPushBack->SetPosition({ 1020,600 });


	myActiveButtonPtrs.push_back(buttonToPushBack);

	return myActiveButtonPtrs;
}
