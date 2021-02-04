#pragma once
#include "BackgroundManager.h"
#include "rapidjson/document.h"

// Filhantering
#include <fstream>
#include <sstream>

namespace Studio
{
	class Player_JsonParser
	{
	public:
		Player_JsonParser(const std::string& aJsonPath);
		~Player_JsonParser() = default;
		Player_JsonParser(const Player_JsonParser&) = default;

		//Movement
		const float GetMinSpeed() const;
		const float GetMaxSpeed() const;
		//Basic Attacks
		const float GetShootCoolDown() const;
		//Rapid Fire
		const float GetRapidFireMaxCooldown() const;
		const float GetRapidFireMaxActiveTime() const;
		const float GetRapidFireAttackSpeed() const;
		//Shield
		const float GetShieldDuration() const;
		const float GetShieldHealth() const;
		const float GetShieldCooldown() const;

		const float GetLayer() const;
		const float GetAcceleration() const;
		const float GetAnimationTurnSpeed() const;

		const Tga2D::Vector2f& GetAmountOfFrames() const;
		const std::pair<VECTOR2F, VECTOR2F>& GetUpAnimationRange() const;
		const std::pair<VECTOR2F, VECTOR2F>& GetDownAnimationRange() const;
		const std::pair<VECTOR2F, VECTOR2F>& GetIdleAnimationRange() const;
		const Tga2D::Vector2f& GetAmountOfFlameFrames() const;

		const std::string& GetImagePath() const;
		const std::string& GetFlameImagePath() const;


		void SetMinSpeed(const float aSpeed);
		void SetMaxSpeed(const float aSpeed);
		void AddToMinSpeed(const float aSpeed);
		void AddToMaxSpeed(const float aSpeed);
		void SetShootCoolDown(const float aCoolDown);
		void SetAnimationTurnSpeed(const float aAnimSpeed);
		void SetRapidFireMaxCooldown(const float aRapidCoolDown);
		void SetRapidFireMaxActiveTime(const float aMaxActiveTime);

		void UpgradeRapidFireCooldownT1();
		void UpgradeRapidFireAttackSpeedT1();
		void UpgradeRapidFireAttackSpeedT2();
		void UpgradeRapidFireDurationT1();
		void UpgradeRapidFireDurationT2();

		void UpgradeBasicAttackSpeedT1();
		void UpgradeBasicAttackSpeedT2();
		void UpgradeBasicAttackSpeedT3();

		void UpgradeShieldDurationT1();
		void UpgradeShieldDurationT2();
		void UpgradeShieldHealthT1();
		void UpgradeShieldHealthT2();
		void UpgradeShieldCooldownT1();
		void UpgradeShieldCooldownT2();

	private:

		bool ValidateJsonDataFloat(const rapidjson::Document& aJsonObject, const std::string& someData);
		bool ValidateNestedJsonDataFloat(const rapidjson::Document& aJsonObject, const char* someData, const char* someNestedData);
		bool ValidateJsonDataString(const rapidjson::Document& aJsonObject, const char* someData);
		bool ValidateNestedJsonDataString(const rapidjson::Document& aJsonObject, const char* someData, const char* someNestedData);

		float myAcceleration;
		float myMinSpeed;
		float myMaxSpeed;

		//Basic attacks
		float myShootCoolDown;
		//Basic Attack Upgrades
		float myBasicAttackSpeedIncreaseT1;
		float myBasicAttackSpeedIncreaseT2;
		float myBasicAttackSpeedIncreaseT3;

		//Rapid fire
		float myRapidFireAttackSpeed;
		float myRapidFireMaxCooldown;
		float myRapidFireMaxActiveTime;
		//Rapid Fire Upgrades
		float myRapidFireCDReductionT1;
		float myRapidFireAttackSpeedIncreaseT1;
		float myRapidFireAttackSpeedIncreaseT2;
		float myRapidFireDurationT1;
		float myRapidFireDurationT2;

		//Shield
		float myShieldDuration;
		float myShieldHealth;
		float myShieldCooldown;
		//Shield Upgrades
		float myShieldDurationUpgradeT1;
		float myShieldDurationUpgradeT2;
		float myShieldHealthUpgradeT1;
		float myShieldHealthUpgradeT2;
		float myShieldCooldownUpgradeT1;
		float myShieldCooldownUpgradeT2;

		float myAnimationTurnSpeed;
		float myLayer;

		std::pair<VECTOR2F, VECTOR2F>myUpAnimationRange;
		std::pair<VECTOR2F, VECTOR2F>myDownAnimationRange;
		std::pair<VECTOR2F, VECTOR2F>myIdleAnimationRange;
		VECTOR2F myAmountOfFrames;
		VECTOR2F myAmountOfFlameFrames;

		std::string myImagepath;
		std::string myFlameImagepath;

	};
}


