#include "stdafx.h"
#include "TypePattern_Enemy.h"
#include "tga2d/sprite/sprite.h"
#include <sstream>

Studio::TypePattern_Enemy::TypePattern_Enemy(rapidjson::Document& aJsonDoc, const std::string& aType) 
{
	myHasExtraColliders = false;
	myIsTerrain = false;
	if (aType[0] == 'T' && aType[1] == '_')
	{
		myIsTerrain = true;
	}
	if (aType[0] == 'P' && aType[1] == 'C')
	{
		myIsPopcorn = true;
	}
	//Movement
	std::string comparison;
	comparison = aJsonDoc["Movement"]["Type"].GetString();
	if (comparison == "Straight")
	{
		myMovementType = Studio::Enums::MovementPattern::Straight;
	}
	if (comparison == "Diagonal")
	{
		myMovementType = Studio::Enums::MovementPattern::Diagonal;
		std::string cornerComparison = aJsonDoc["Movement"]["SpawnInCorner"].GetString();
		if (cornerComparison == "Bottom")
		{
			myDiagonalIsTop = false;
		}
		if (cornerComparison == "Top")
		{
			myDiagonalIsTop = true;
		}
	}
	if (comparison == "Wave")
	{
		myMovementType = Studio::Enums::MovementPattern::Wave;
		myHorizontalSpeed = aJsonDoc["Movement"]["HorizontalSpeed"].GetFloat();
		myVerticalSpeed = aJsonDoc["Movement"]["VerticalSpeed"].GetFloat();
		myWaveHeigth = aJsonDoc["Movement"]["Height"].GetFloat();

	}
	if (comparison == "Bobbing")
	{
		myMovementType = Studio::Enums::MovementPattern::Bobbing;
		myBobbingHeigth = aJsonDoc["Movement"]["Height"].GetFloat();
	}
	if (comparison == "Seeking")
	{
		myMovementType = Studio::Enums::MovementPattern::Seeking;
		myAcceleration = aJsonDoc["Movement"]["Acceleration"].GetFloat();
	}

	myStartingHealth = aJsonDoc["HealthPoints"].GetFloat();

	if (aJsonDoc["Movement"].HasMember("Speed"))
	{
		mySpeed = aJsonDoc["Movement"]["Speed"].GetFloat();
	}
	if (aJsonDoc["Bullet"].HasMember("Interval"))
	{
		myShootInterval = aJsonDoc["Bullet"]["Interval"].GetFloat() * 0.001;
	}
	else
	{
		myShootInterval = 1000000;
	}
	myBulletSpeed = aJsonDoc["Bullet"]["Speed"].GetFloat();

	if (aJsonDoc.HasMember("Animation"))
	{
#define JSON aJsonDoc["Animation"]
		std::string path = "sprites/";
		path.append(JSON["ImagePath"].GetString());
		path.append(".dds");
		myImagePath = path;

		
		if (!JSON["AmountOfFrames"]["X"].IsString() && !JSON["AmountOfFrames"]["Y"].IsString())
		{
			myAmountOfFrames.x = JSON["AmountOfFrames"]["X"].GetFloat();
			myAmountOfFrames.y = JSON["AmountOfFrames"]["Y"].GetFloat();
			myIsAnimating = true;

			//if (JSON["IdleAnimationRange"]["Type"].GetString() == "Custom")
			//{
			//	std::stringstream ss = JSON["IdleAnimationRange"]["Frames"].GetString();
			//	
			//
			//	myUsingCustomIdleFrames = true;
			//}
			if (JSON["IdleAnimationRange"]["Type"].GetString() == "Start/End")
			{
				myUsingCustomIdleFrames = false;
				if (!JSON["IdleAnimationRange"]["FrameStartX"].IsString())
				{
					myIdleAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameStartX"].GetFloat();
				}
				if (!JSON["IdleAnimationRange"]["FrameStartY"].IsString())
				{
					myIdleAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameStartY"].GetFloat();
				}
				if (!JSON["IdleAnimationRange"]["FrameEndX"].IsString())
				{
					myIdleAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameEndX"].GetFloat();
				}
				if (!JSON["IdleAnimationRange"]["FrameEndY"].IsString())
				{
					myIdleAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameEndY"].GetFloat();
				}
			}
			if (JSON["UpAnimationRange"]["Type"].GetString() == "Start/End")
			{
				myUsingCustomIdleFrames = false;
				if (!JSON["UpAnimationRange"]["FrameStartX"].IsString())
				{
					myUpAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameStartX"].GetFloat();
				}
				if (!JSON["UpAnimationRange"]["FrameStartY"].IsString())
				{
					myUpAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameStartY"].GetFloat();
				}
				if (!JSON["UpAnimationRange"]["FrameEndX"].IsString())
				{
					myUpAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameEndX"].GetFloat();
				}
				if (!JSON["UpAnimationRange"]["FrameEndY"].IsString())
				{
					myUpAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameEndY"].GetFloat();
				}
			}
			if (JSON["DownAnimationRange"]["Type"].GetString() == "Start/End")
			{
				myUsingCustomIdleFrames = false;
				if (!JSON["DownAnimationRange"]["FrameStartX"].IsString())
				{
					myDownAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameStartX"].GetFloat();
				}
				if (!JSON["DownAnimationRange"]["FrameStartY"].IsString())
				{
					myDownAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameStartY"].GetFloat();
				}
				if (!JSON["DownAnimationRange"]["FrameEndX"].IsString())
				{
					myDownAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameEndX"].GetFloat();
				}
				if (!JSON["DownAnimationRange"]["FrameEndY"].IsString())
				{
					myDownAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameEndY"].GetFloat();
				}
			}
		}
		else
		{
			myIsAnimating = false;
		}
	}
	else
	{
		myIsAnimating = false;
		myImagePath = "sprites/assets/enemies/enemyShip1/enemyShip1.dds";
	}

}

void Studio::TypePattern_Enemy::CreateCollissionObjects(rapidjson::Document& aJsonDoc)
{
	myHasExtraColliders = true;
	if (aJsonDoc.HasMember("Circle") && aJsonDoc["Circle"].IsArray())
	{
		auto colliders = aJsonDoc["Circle"].GetArray();
		for (int i = 0; i < colliders.Size(); i++)
		{
			std::pair<float, VECTOR2F> tempPair(
				colliders[i]["Radius"].GetFloat(),
				{ colliders[i]["PositionX"].GetFloat(), colliders[i]["PositionY"].GetFloat() }
			);
			myCircleColliders.push_back(tempPair);
		}
	}
	if (aJsonDoc.HasMember("Box") && aJsonDoc["Box"].IsArray())
	{
		auto colliders = aJsonDoc["Box"].GetArray();
		for (int i = 0; i < colliders.Size(); i++)
		{
			std::pair<VECTOR2F, VECTOR2F> tempPair(
				{ colliders[i]["PositionX"].GetFloat(), colliders[i]["PositionY"].GetFloat() },
				{ colliders[i]["WidthX"].GetFloat(), colliders[i]["WidthY"].GetFloat() }
			);
			myBoxColliders.push_back(tempPair);
		}
	}
}

const Studio::Enums::MovementPattern Studio::TypePattern_Enemy::GetMovementType() const { return myMovementType; }

const float Studio::TypePattern_Enemy::GetStartHealth() const { return myStartingHealth; }

const float Studio::TypePattern_Enemy::GetSpeed() const{ return mySpeed;}

const float Studio::TypePattern_Enemy::GetShootInterval() const{ return myShootInterval;}

const float Studio::TypePattern_Enemy::GetBulletSpeed() const{ return myBulletSpeed;}

const float Studio::TypePattern_Enemy::GetHorizontalSpeed() const { return myHorizontalSpeed; }

const float Studio::TypePattern_Enemy::GetVerticalSpeed() const { return myVerticalSpeed; }

const float Studio::TypePattern_Enemy::GetWaveHeigth() const { return myWaveHeigth; }

const float Studio::TypePattern_Enemy::GetBobbingHeigth() const { return myBobbingHeigth; }

const float Studio::TypePattern_Enemy::GetAcceleration() const { return myAcceleration; }

const Tga2D::Vector2f& Studio::TypePattern_Enemy::GetAmountOfFrames() const{ return myAmountOfFrames;}

const std::pair<VECTOR2F, VECTOR2F>& Studio::TypePattern_Enemy::GetUpAnimationRange() const { return myUpAnimationRange;}

const std::pair<VECTOR2F, VECTOR2F>& Studio::TypePattern_Enemy::GetDownAnimationRange() const {	return myDownAnimationRange;}

const std::pair<VECTOR2F, VECTOR2F>& Studio::TypePattern_Enemy::GetIdleAnimationRange() const {	return myIdleAnimationRange;}

const std::vector<float> Studio::TypePattern_Enemy::GetUpAnimationCustomFrames() const { return myUpAnimationCustomFrames;}

const std::vector<float> Studio::TypePattern_Enemy::GetDownAnimationCustomFrames() const { return myDownAnimationCustomFrames;}

const std::vector<float> Studio::TypePattern_Enemy::GetIdleAnimationCustomFrames() const { return myIdleAnimationCustomFrames;}

const bool Studio::TypePattern_Enemy::GetIsAnimating() const { return myIsAnimating;}

const bool Studio::TypePattern_Enemy::GetIsTerrain() const { return myIsTerrain; }

const bool Studio::TypePattern_Enemy::GetIsPopcorn() const { return myIsPopcorn; }

const bool Studio::TypePattern_Enemy::GetUsingCustomUpFrames() const { return myUsingCustomUpFrames;}

const bool Studio::TypePattern_Enemy::GetUsingCustomDownFrames() const { return myUsingCustomDownFrames;}

const bool Studio::TypePattern_Enemy::GetUsingCustomIdleFrames() const { return myUsingCustomIdleFrames;}

const bool Studio::TypePattern_Enemy::GetDiagonalIsTop() const { return myDiagonalIsTop; }

const bool Studio::TypePattern_Enemy::GetHasExtraCollission() const { return myHasExtraColliders; }

const std::vector<std::pair<float, VECTOR2F>>& Studio::TypePattern_Enemy::GetCircleColliders() { return myCircleColliders; }

const std::vector<std::pair<VECTOR2F, VECTOR2F>>& Studio::TypePattern_Enemy::GetBoxColliders() { return myBoxColliders; }

const std::string& Studio::TypePattern_Enemy::GetImagePath() const { return myImagePath; }
