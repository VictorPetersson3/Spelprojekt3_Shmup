#include "stdafx.h"
#include "Player_JsonParser.h"

Studio::Player_JsonParser::Player_JsonParser(const std::string& aJsonPath)
{
	const char* playerDataPath = aJsonPath.c_str();

	rapidjson::Document document;

	std::string text;
	std::fstream file;
	file.open(playerDataPath);
	{
		std::string line;
		while (std::getline(file, line))
		{
			text.append(line);
			printf("%s\n", line.c_str());
		}
	}
	file.close();
	document.Parse(text.c_str());
	//printf("Path: %s \nDocument%s", levelPath, text.c_str());

	//----------- FLOATS

	if (validateJsonDataFloat(document, "MinSpeed"))
	{
		myMinSpeed = document["MinSpeed"].GetFloat();
	}
	if (validateJsonDataFloat(document, "MaxSpeed"))
	{
		myMaxSpeed = document["MaxSpeed"].GetFloat();
	}
	if (validateJsonDataFloat(document, "ShootCoolDown"))
	{
		myShootCoolDown = document["ShootCoolDown"].GetFloat();
	}

	if (validateJsonDataFloat(document, "RapidFireMaxCooldown"))
	{
		myRapidFireMaxCooldown = document["RapidFireMaxCooldown"].GetFloat();
	}

	if (validateJsonDataFloat(document, "RapidFireMaxActiveTime"))
	{
		myRapidFireMaxActiveTime = document["RapidFireMaxActiveTime"].GetFloat();
	}

	if (validateJsonDataFloat(document, "AnimationTurnSpeed"))
	{
		myAnimationTurnSpeed = document["AnimationTurnSpeed"].GetFloat();
	}

	if (validateJsonDataFloat(document, "LayerOrder"))
	{
		myLayer = document["LayerOrder"].GetFloat();
	}

	if (validateJsonDataFloat(document, "ShootCDReductionPercentage"))
	{
		myCDReductionPercentage = document["ShootCDReductionPercentage"].GetFloat();
	}


	///-------- STRINGS
	if (validateJsonDataString(document, "ImagePath"))
	{
		myImagepath = document["ImagePath"].GetString();
	}

	if (validateJsonDataString(document, "FlameImagePath"))
	{
		myFlameImagepath = document["FlameImagePath"].GetString();
	}


	//-------------AnimationData

	//Up Animation
	if (validateNestedJsonDataFloat(document, "UpAnimationRange", "FrameStartX"))
	{
		myUpAnimationRange.first.x = document["UpAnimationRange"]["FrameStartX"].GetFloat();
	}

	if (validateNestedJsonDataFloat(document, "UpAnimationRange", "FrameStartY"))
	{
		myUpAnimationRange.first.y = document["UpAnimationRange"]["FrameStartY"].GetFloat();
	}

	if (validateNestedJsonDataFloat(document, "UpAnimationRange", "FrameEndX"))
	{
		myUpAnimationRange.second.x = document["UpAnimationRange"]["FrameEndX"].GetFloat();
	}

	if (validateNestedJsonDataFloat(document, "UpAnimationRange", "FrameEndY"))
	{
		myUpAnimationRange.second.y = document["UpAnimationRange"]["FrameEndY"].GetFloat();
	}

	//Down Animation
	 
	if (validateNestedJsonDataFloat(document, "DownAnimationRange", "FrameStartX"))
	{
		myDownAnimationRange.first.x = document["DownAnimationRange"]["FrameStartX"].GetFloat();
	}

	if (validateNestedJsonDataFloat(document, "DownAnimationRange", "FrameStartY"))
	{
		myDownAnimationRange.first.y = document["DownAnimationRange"]["FrameStartY"].GetFloat();
	}

	if (validateNestedJsonDataFloat(document, "DownAnimationRange", "FrameEndX"))
	{
		myDownAnimationRange.second.x = document["DownAnimationRange"]["FrameEndX"].GetFloat();
	}

	if (validateNestedJsonDataFloat(document, "DownAnimationRange", "FrameEndY"))
	{
		myDownAnimationRange.second.y = document["DownAnimationRange"]["FrameEndY"].GetFloat();
	}

	//Idle Animation
	
	if (validateNestedJsonDataFloat(document, "IdleAnimationRange", "FrameStartX"))
	{
		myIdleAnimationRange.first.x = document["IdleAnimationRange"]["FrameStartX"].GetFloat();
	}

	if (validateNestedJsonDataFloat(document, "IdleAnimationRange", "FrameStartY"))
	{
		myIdleAnimationRange.first.y = document["IdleAnimationRange"]["FrameStartY"].GetFloat();
	}

	if (validateNestedJsonDataFloat(document, "IdleAnimationRange", "FrameEndX"))
	{
		myIdleAnimationRange.second.x = document["IdleAnimationRange"]["FrameEndX"].GetFloat();
	}

	if (validateNestedJsonDataFloat(document, "IdleAnimationRange", "FrameEndY"))
	{
		myIdleAnimationRange.second.y = document["IdleAnimationRange"]["FrameEndY"].GetFloat();
	}

	// Amount Of Frames

	if (validateNestedJsonDataFloat(document, "AmountOfFrames", "X"))
	{
		myAmountOfFrames.x = document["AmountOfFrames"]["X"].GetFloat();
	}

	if (validateNestedJsonDataFloat(document, "AmountOfFrames", "Y"))
	{
		myAmountOfFrames.y = document["AmountOfFrames"]["Y"].GetFloat();
	}

	//Amount of Flame Frames

	if (validateNestedJsonDataFloat(document, "AmountOfFramesFlame", "X"))
	{
		myAmountOfFlameFrames.x = document["AmountOfFramesFlame"]["X"].GetFloat();
	}

	if (validateNestedJsonDataFloat(document, "AmountOfFramesFlame", "Y"))
	{
		myAmountOfFlameFrames.y = document["AmountOfFramesFlame"]["Y"].GetFloat();
	}
}

const float Studio::Player_JsonParser::GetMinSpeed() const { return myMinSpeed;}

const float Studio::Player_JsonParser::GetMaxSpeed() const { return myMaxSpeed; }

const float Studio::Player_JsonParser::GetShootCoolDown() const { return myShootCoolDown; }

const float Studio::Player_JsonParser::GetCDReductionPercentage() const { return myCDReductionPercentage; }

const float Studio::Player_JsonParser::GetAnimationTurnSpeed() const { return myAnimationTurnSpeed; }

const float Studio::Player_JsonParser::GetRapidFireMaxCooldown() const { return myRapidFireMaxCooldown; }

const float Studio::Player_JsonParser::GetRapidFireMaxActiveTime() const { return myRapidFireMaxActiveTime; }

const float Studio::Player_JsonParser::GetLayer() const { return myLayer; }

const Tga2D::Vector2f& Studio::Player_JsonParser::GetAmountOfFrames() const { return myAmountOfFrames; }

const std::pair<VECTOR2F, VECTOR2F>& Studio::Player_JsonParser::GetUpAnimationRange() const { return myUpAnimationRange; }

const std::pair<VECTOR2F, VECTOR2F>& Studio::Player_JsonParser::GetDownAnimationRange() const { return myDownAnimationRange; }

const std::pair<VECTOR2F, VECTOR2F>& Studio::Player_JsonParser::GetIdleAnimationRange() const { return myIdleAnimationRange; }

const Tga2D::Vector2f& Studio::Player_JsonParser::GetAmountOfFlameFrames() const { return myAmountOfFlameFrames; }

const std::string& Studio::Player_JsonParser::GetImagePath() const { return myImagepath; }

const std::string& Studio::Player_JsonParser::GetFlameImagePath() const { return myFlameImagepath; }

void Studio::Player_JsonParser::SetMinSpeed(const float aSpeed)
{
	myMinSpeed = aSpeed;
}

void Studio::Player_JsonParser::SetMaxSpeed(const float aSpeed)
{
	myMaxSpeed = aSpeed;
}

void Studio::Player_JsonParser::AddToMinSpeed(const float aSpeed)
{
	myMinSpeed += aSpeed;
}

void Studio::Player_JsonParser::AddToMaxSpeed(const float aSpeed)
{
	myMaxSpeed += aSpeed;
}

void Studio::Player_JsonParser::SetShootCoolDown(const float aCoolDown)
{
	myShootCoolDown = aCoolDown;
}

void Studio::Player_JsonParser::SetAnimationTurnSpeed(const float aAnimSpeed)
{
	myAnimationTurnSpeed = aAnimSpeed;
}

void Studio::Player_JsonParser::SetRapidFireMaxCooldown(const float aRapidCoolDown)
{
	myRapidFireMaxCooldown = aRapidCoolDown;
}

void Studio::Player_JsonParser::SetRapidFireMaxActiveTime(const float aMaxActiveTime)
{
	myRapidFireMaxActiveTime = aMaxActiveTime;
}

void Studio::Player_JsonParser::SetCDReductionPercentage(const float aCDReduction)
{
	myCDReductionPercentage = aCDReduction;
}

void Studio::Player_JsonParser::AddToCDReductionPercentage(const float aCDReduction)
{
	myCDReductionPercentage += aCDReduction;
}


bool Studio::Player_JsonParser::validateJsonDataFloat(const rapidjson::Document& aJsonObject, const std::string& someData)
{
	if (aJsonObject.HasMember(someData.c_str()) && aJsonObject[someData.c_str()].IsFloat())
	{
		return true;
	}
	else
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing or incorrectly Typed, must be a number.\n", someData);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	return false;
}

bool Studio::Player_JsonParser::validateNestedJsonDataFloat(const rapidjson::Document& aJsonObject, const char* someData, const char* someNestedData)
{

	if (aJsonObject[someData].HasMember(someNestedData) && aJsonObject[someData][someNestedData].IsFloat())
	{
		return true;
	}
	else
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s, %s is missing or incorrectly Typed, must be a number.\n", someData, someNestedData);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	return false;
}

bool Studio::Player_JsonParser::validateJsonDataString(const rapidjson::Document& aJsonObject, const char* someData)
{
	if (aJsonObject.HasMember(someData) && aJsonObject[someData].IsString())
	{
		return true;
	}
	else
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing or incorrectly Typed, must be a text in " ". \n", someData);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}

	return false;
}

bool Studio::Player_JsonParser::validateNestedJsonDataString(const rapidjson::Document& aJsonObject, const char* someData, const char* someNestedData)
{

	if (aJsonObject[someData].HasMember(someNestedData) && aJsonObject[someData][someNestedData].IsFloat())
	{
		return true;
	}
	else
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s, %s is missing or incorrectly Typed, must be a text in " ". \n", someData, someNestedData);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	return false;
}
