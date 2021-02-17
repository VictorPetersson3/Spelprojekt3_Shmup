#include "stdafx.h"
#include "TypePattern_Enemy.h"
#include "tga2d/sprite/sprite.h"
#include <sstream>

Studio::TypePattern_Enemy::TypePattern_Enemy(rapidjson::Document& aJsonDoc, const std::string& aType) 
{
	myHasExtraColliders = false;
	myIsTerrain = false;
	myIsTurret = false;
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
		if (myShootInterval == 0)
		{
			myShootInterval = 1000000;
		}
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

		myUpAnimationRange.first.x = 1;
		myUpAnimationRange.first.y = 1;
		myUpAnimationRange.second.x = 1;
		myUpAnimationRange.second.y = 1;

		myDownAnimationRange.first.x = 1;
		myDownAnimationRange.first.y = 1;
		myDownAnimationRange.second.x = 1;
		myDownAnimationRange.second.y = 1;

		myIdleAnimationRange.first.x = 1;
		myIdleAnimationRange.first.y = 1;
		myIdleAnimationRange.second.x = 1;
		myIdleAnimationRange.second.y = 1;

		if (!JSON["AmountOfFrames"]["X"].IsString() && !JSON["AmountOfFrames"]["Y"].IsString() || JSON["AmountOfFrames"]["Y"].GetFloat() != 1 && JSON["AmountOfFrames"]["X"].GetFloat() != 1)
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
			if (JSON["IdleAnimationRange"]["Type"].GetString()[0] == 'S')
			{
				myUsingCustomIdleFrames = false;
				if (!JSON["IdleAnimationRange"]["FrameStartX"].IsString())
				{
					myIdleAnimationRange.first.x = JSON["IdleAnimationRange"]["FrameStartX"].GetFloat();
					if (myIdleAnimationRange.first.x == 0)
					{
						myIdleAnimationRange.first.x = 1;
					}
				}
				if (!JSON["IdleAnimationRange"]["FrameStartY"].IsString())
				{
					myIdleAnimationRange.first.y = JSON["IdleAnimationRange"]["FrameStartY"].GetFloat();
					if (myIdleAnimationRange.first.y == 0)
					{
						myIdleAnimationRange.first.y = 1;
					}
				}
				if (!JSON["IdleAnimationRange"]["FrameEndX"].IsString())
				{
					myIdleAnimationRange.second.x = JSON["IdleAnimationRange"]["FrameEndX"].GetFloat();
					if (myIdleAnimationRange.second.x == 0)
					{
						myIdleAnimationRange.second.x = 1;
					}
				}
				if (!JSON["IdleAnimationRange"]["FrameEndY"].IsString())
				{
					myIdleAnimationRange.second.y = JSON["IdleAnimationRange"]["FrameEndY"].GetFloat();
					if (myIdleAnimationRange.second.x == 0)
					{
						myIdleAnimationRange.second.x = 1;
					}
				}
			}
			if (JSON["UpAnimationRange"]["Type"].GetString()[0] == 'S')
			{
				myUsingCustomIdleFrames = false;
				if (!JSON["UpAnimationRange"]["FrameStartX"].IsString())
				{
					myUpAnimationRange.first.x = JSON["UpAnimationRange"]["FrameStartX"].GetFloat();
					if (myUpAnimationRange.first.x == 0)
					{
						myUpAnimationRange.first.x = 1;
					}
				}
				if (!JSON["UpAnimationRange"]["FrameStartY"].IsString())
				{
					myUpAnimationRange.first.y = JSON["UpAnimationRange"]["FrameStartY"].GetFloat();
					if (myUpAnimationRange.first.y == 0)
					{
						myUpAnimationRange.first.y = 1;
					}
				}
				if (!JSON["UpAnimationRange"]["FrameEndX"].IsString())
				{
					myUpAnimationRange.second.x = JSON["UpAnimationRange"]["FrameEndX"].GetFloat();
					if (myUpAnimationRange.second.x == 0)
					{
						myUpAnimationRange.second.x = 1;
					}
				}
				if (!JSON["UpAnimationRange"]["FrameEndY"].IsString())
				{
					myUpAnimationRange.second.y = JSON["UpAnimationRange"]["FrameEndY"].GetFloat();
					if (myUpAnimationRange.second.y == 0)
					{
						myUpAnimationRange.second.y = 1;
					}
					printf("UpAnimation Range first x: %f y: %f Second x: %f y: %f", myUpAnimationRange.first.x, myUpAnimationRange.first.y, myUpAnimationRange.second.x, myUpAnimationRange.second.y);
				}
			}
			if (JSON["DownAnimationRange"]["Type"].GetString()[0] == 'S')
			{
				myUsingCustomIdleFrames = false;
				if (!JSON["DownAnimationRange"]["FrameStartX"].IsString())
				{
					myDownAnimationRange.first.x = JSON["DownAnimationRange"]["FrameStartX"].GetFloat();
					if (myUpAnimationRange.first.x == 0)
					{
						myUpAnimationRange.first.x = 1;
					}
				}
				if (!JSON["DownAnimationRange"]["FrameStartY"].IsString())
				{
					myDownAnimationRange.first.y = JSON["DownAnimationRange"]["FrameStartY"].GetFloat();
					if (myUpAnimationRange.first.y == 0)
					{
						myUpAnimationRange.first.y = 1;
					}
				}
				if (!JSON["DownAnimationRange"]["FrameEndX"].IsString())
				{
					myDownAnimationRange.second.x = JSON["DownAnimationRange"]["FrameEndX"].GetFloat();
					if (myUpAnimationRange.second.x == 0)
					{
						myUpAnimationRange.second.x = 1;
					}
				}
				if (!JSON["DownAnimationRange"]["FrameEndY"].IsString())
				{
					myDownAnimationRange.second.y = JSON["DownAnimationRange"]["FrameEndY"].GetFloat();
					if (myUpAnimationRange.second.y == 0)
					{
						myUpAnimationRange.second.y = 1;
					}
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

void Studio::TypePattern_Enemy::CreateTurretObject(rapidjson::Document& aJsonDoc)
{
	myIsTurret = true;
	myTurretRotationSpeed = aJsonDoc["RotationSpeed"].GetFloat();
	myTurretPivot.x = aJsonDoc["PivotX"].GetFloat();
	myTurretPivot.y = aJsonDoc["PivotY"].GetFloat();
	myTurretPath = aJsonDoc["ImagePath"].GetString();
	myTurretSpawnPoint.x = aJsonDoc["SpawnPositionX"].GetFloat();
	myTurretSpawnPoint.y = aJsonDoc["SpawnPositionY"].GetFloat();
	myTurretBulletSpawnPoint.x = aJsonDoc["BulletSpawnPositionX"].GetFloat();
	myTurretBulletSpawnPoint.y = aJsonDoc["BulletSpawnPositionY"].GetFloat();
	myIsUpright = aJsonDoc["IsUpright"].GetBool();
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

const float Studio::TypePattern_Enemy::GetTurretRotationSpeed() const { return myTurretRotationSpeed; }

const Tga2D::Vector2f& Studio::TypePattern_Enemy::GetTurretPivot() const { return myTurretPivot; }

const Tga2D::Vector2f& Studio::TypePattern_Enemy::GetTurretSpawnPoint() const { return myTurretSpawnPoint; }

const Tga2D::Vector2f& Studio::TypePattern_Enemy::GetTurretBulletSpawnPoint() const { return myTurretBulletSpawnPoint; }

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

const bool Studio::TypePattern_Enemy::GetIsTurret() const {return myIsTurret; }

const bool Studio::TypePattern_Enemy::GetIsUpright() const { return myIsUpright; }

const std::vector<std::pair<float, VECTOR2F>>& Studio::TypePattern_Enemy::GetCircleColliders() { return myCircleColliders; }

const std::vector<std::pair<VECTOR2F, VECTOR2F>>& Studio::TypePattern_Enemy::GetBoxColliders() { return myBoxColliders; }

const std::string& Studio::TypePattern_Enemy::GetImagePath() const { return myImagePath; }

const std::string& Studio::TypePattern_Enemy::GetTurretPipeImagePath() const { return myTurretPath; }
