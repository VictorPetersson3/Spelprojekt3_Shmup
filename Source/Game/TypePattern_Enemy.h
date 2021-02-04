#pragma once
#include "rapidjson/document.h"
#include "Enums.h"


namespace Tga2D
{
	class CSprite;
}
namespace Studio
{

	class TypePattern_Enemy
	{
	public:
		TypePattern_Enemy(rapidjson::Document& aJsonDoc, const std::string& aType);
		~TypePattern_Enemy() = default;

		void CreateCollissionObjects(rapidjson::Document& aJsonDoc);

		const Enums::MovementPattern GetMovementType() const;
		const float GetStartHealth() const;
		const float GetSpeed() const;
		const float GetShootInterval() const;
		const float GetBulletSpeed() const;

		const float GetHorizontalSpeed() const;
		const float GetVerticalSpeed() const;
		const float GetWaveHeigth() const;

		const float GetBobbingHeigth() const;

		const float GetAcceleration() const;

		const Tga2D::Vector2f& GetAmountOfFrames() const;
		const std::pair<VECTOR2F, VECTOR2F>& GetUpAnimationRange() const;
		const std::pair<VECTOR2F, VECTOR2F>& GetDownAnimationRange() const;
		const std::pair<VECTOR2F, VECTOR2F>& GetIdleAnimationRange() const;
		const std::vector<float> GetUpAnimationCustomFrames() const;
		const std::vector<float> GetDownAnimationCustomFrames() const;
		const std::vector<float> GetIdleAnimationCustomFrames() const;

		const bool GetIsAnimating() const;
		const bool GetIsTerrain() const;
		const bool GetIsPopcorn() const;
		const bool GetUsingCustomUpFrames() const;
		const bool GetUsingCustomDownFrames() const;
		const bool GetUsingCustomIdleFrames() const;
		
		const bool GetDiagonalIsTop() const;

		const bool GetHasExtraCollission() const;

		const std::vector<std::pair<float, VECTOR2F>>& GetCircleColliders();
		const std::vector<std::pair<VECTOR2F, VECTOR2F>>& GetBoxColliders();


		const std::string& GetImagePath() const;

	private:
		Enums::MovementPattern myMovementType;
		float myStartingHealth;
		float mySpeed;
		float myShootInterval;
		float myBulletSpeed;

		//Wave Variabels
		float myHorizontalSpeed;
		float myVerticalSpeed;
		float myWaveHeigth;

		//Bobbing Variables
		float myBobbingHeigth;

		//Seeking Variables
		float myAcceleration;

		//Animation
		Tga2D::Vector2f myAmountOfFrames;
		std::pair<VECTOR2F, VECTOR2F>myUpAnimationRange;
		std::pair<VECTOR2F, VECTOR2F>myDownAnimationRange;
		std::pair<VECTOR2F, VECTOR2F>myIdleAnimationRange;
		std::vector<float> myUpAnimationCustomFrames;
		std::vector<float> myDownAnimationCustomFrames;
		std::vector<float> myIdleAnimationCustomFrames;

		bool myUsingCustomUpFrames = false;
		bool myUsingCustomDownFrames = false;
		bool myUsingCustomIdleFrames = false;
		bool myIsAnimating = false;

		bool myIsTerrain = false;
		bool myIsPopcorn = false; // Make Getter

		bool myDiagonalIsTop;

		std::string myImagePath;
		//Key for Bullet Types as well as imagePath
		std::string myBulletImagePath;
		//Sätta in support för alla olika Types av Movement

		//Kollission
		bool myHasExtraColliders;

		std::vector<std::pair<float, VECTOR2F>> myCircleColliders;
		std::vector<std::pair<VECTOR2F, VECTOR2F>> myBoxColliders;

	};
}


