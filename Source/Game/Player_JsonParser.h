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

		const float GetMinSpeed() const;
		const float GetMaxSpeed() const;
		const float GetShootCoolDown() const;
		const float GetCDReductionPercentage() const;
		const float GetAnimationTurnSpeed() const;
		const float GetRapidFireMaxCooldown() const;
		const float GetRapidFireMaxActiveTime() const;
		const float GetLayer() const;
		const float GetAcceleration() const;

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
		void SetCDReductionPercentage(const float aCDReduction);
		void AddToCDReductionPercentage(const float aCDReduction);

	private:

		bool validateJsonDataFloat(const rapidjson::Document& aJsonObject, const std::string& someData);
		bool validateNestedJsonDataFloat(const rapidjson::Document& aJsonObject, const char* someData, const char* someNestedData);
		bool validateJsonDataString(const rapidjson::Document& aJsonObject, const char* someData);
		bool validateNestedJsonDataString(const rapidjson::Document& aJsonObject, const char* someData, const char* someNestedData);

		float myAcceleration;
		float myMinSpeed;
		float myMaxSpeed;
		float myShootCoolDown;
		float myCDReductionPercentage;
		float myRapidFireMaxCooldown;
		float myRapidFireMaxActiveTime;
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


