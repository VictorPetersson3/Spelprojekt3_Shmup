#include "stdafx.h"
#include "BackgroundManager.h"
#include "rapidjson/document.h"

// Filhantering
#include <fstream>
#include <sstream>


#include "RendererAccessor.h"
#include "Renderer.h"
#include "BackgroundObject.h"

#include <iostream>

void Studio::BackgroundManager::CreateBackground(const char& aBackgroundPath)
{
	char levelPath = aBackgroundPath;

	rapidjson::Document document;

	std::string text;
	std::fstream file;
	file.open(&aBackgroundPath);
	{
		std::string line;
		while (std::getline(file, line))
		{
			text.append(line);
		}
	}
	file.close();
	document.Parse(text.c_str());
	
	if (document.HasMember("BackgroundImage"))
	{
		printf_s("===JSON===\n%s\n==========\n", text.c_str());
		std::vector<std::string> types;
		int myTypeIndex = 0;
		bool isNewType = true;
		DebugJsonDocNonIterator(document["BackgroundImage"], "BackgroundImage");
		for (int j = 0; j < types.size(); j++)
		{
			if (types.at(j) == document["BackgroundImage"]["Type"].GetString())
			{
				myTypeIndex = j;
				isNewType = false;
				break;
			}
		}
		if (isNewType)
		{
			types.push_back(document["BackgroundImage"]["Type"].GetString());
			myBackgroundFactory.InitBackGroundObject(document["BackgroundImage"], types.at(myTypeIndex));
		}
		myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(types.at(myTypeIndex), document["BackgroundImage"]));			
	}
	else
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: \"%s\" is missing BackgroundImage\n", levelPath);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (document.HasMember("MountainLayer") && document["MountainLayer"].IsArray())
	{
		auto backgroundObjects = document["MountainLayer"].GetArray();
		printf_s("===JSON===\n%s\n==========\n", text.c_str());
		std::vector<std::string> types;

		for (rapidjson::SizeType i = 0; i < backgroundObjects.Size(); i++)
		{
			int myTypeIndex = 0;
			bool isNewType = true;
			DebugJsonDocNonIterator(backgroundObjects[i], "MountainLayer");
			for (int j = 0; j < types.size(); j++)
			{
				if (types.at(j) == backgroundObjects[i]["Type"].GetString())
				{
					myTypeIndex = j;
					isNewType = false;
					break;
				}
				myTypeIndex = j + 1;
			}
			if (isNewType)
			{
				types.push_back(backgroundObjects[i]["Type"].GetString());
				myBackgroundFactory.InitBackGroundObject(backgroundObjects[i], types.at(myTypeIndex));
			}
			if (backgroundObjects[i]["CreateMany"].GetBool())
			{
				for (int k = 0; k < backgroundObjects[i]["Amount"].GetFloat(); k++)
				{
					myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(types.at(myTypeIndex), backgroundObjects[i], k));
				}
			}
			else
			{
				myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(types.at(myTypeIndex), backgroundObjects[i]));
			}
		}
	}
	else
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: \"%s\" is missing MountainLayer\n", levelPath);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (document.HasMember("GradientImage"))
	{
		printf_s("===JSON===\n%s\n==========\n", text.c_str());

		std::vector<std::string> types;

		int myTypeIndex = 0;
		bool isNewType = true;
		DebugJsonDocNonIterator(document["GradientImage"], "GradientImage");
		
		for (int j = 0; j < types.size(); j++)
		{
			if (types.at(j) == document["GradientImage"]["Type"].GetString())
			{
				myTypeIndex = j;
				isNewType = false;
				break;
			}
		}
		if (isNewType)
		{
			types.push_back(document["GradientImage"]["Type"].GetString());
			myBackgroundFactory.InitBackGroundObject(document["GradientImage"], types.at(myTypeIndex));
		}
		myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(types.at(myTypeIndex), document["GradientImage"]));
	}
	else
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: \"%s\" is missing GradientImage\n", levelPath);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (document.HasMember("GroundLayer") && document["GroundLayer"].IsArray())
	{
		auto backgroundObjects = document["GroundLayer"].GetArray();
		printf_s("===JSON===\n%s\n==========\n", text.c_str());
		std::vector<std::string> types;

		for (rapidjson::SizeType i = 0; i < backgroundObjects.Size(); i++)
		{
			int myTypeIndex = 0;
			bool isNewType = true;
			DebugJsonDocNonIterator(backgroundObjects[i], "GroundLayer");
			for (int j = 0; j < types.size(); j++)
			{
				if (types.at(j) == backgroundObjects[i]["Type"].GetString())
				{
					myTypeIndex = j;
					isNewType = false;
					break;
				}
				myTypeIndex = j + 1;
			}
			if (isNewType)
			{
				types.push_back(backgroundObjects[i]["Type"].GetString());
				myBackgroundFactory.InitBackGroundObject(backgroundObjects[i], types.at(myTypeIndex));
			}
			if (backgroundObjects[i]["CreateMany"].GetBool())
			{
				for (int k = 0; k < backgroundObjects[i]["Amount"].GetFloat(); k++)
				{
					myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(types.at(myTypeIndex), backgroundObjects[i], k));
				}
			}
			else
			{
				myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(types.at(myTypeIndex), backgroundObjects[i]));
			}
		}
	}
	else
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: \"%s\" is missing GroundLayer\n", levelPath);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (document.HasMember("MiddlegroundLayer") && document["MiddlegroundLayer"].IsArray())
	{
		auto backgroundObjects = document["MiddlegroundLayer"].GetArray();
		printf_s("===JSON===\n%s\n==========\n", text.c_str());
		std::vector<std::string> types;

		for (rapidjson::SizeType i = 0; i < backgroundObjects.Size(); i++)
		{
			int myTypeIndex = 0;
			bool isNewType = true;
			DebugJsonDocNonIterator(backgroundObjects[i], "MiddlegroundLayer");
			for (int j = 0; j < types.size(); j++)
			{
				if (types.at(j) == backgroundObjects[i]["Type"].GetString())
				{
					myTypeIndex = j;
					isNewType = false;
					break;
				}
				myTypeIndex = j + 1;
			}
			if (isNewType)
			{
				types.push_back(backgroundObjects[i]["Type"].GetString());
				myBackgroundFactory.InitBackGroundObject(backgroundObjects[i], types.at(myTypeIndex));
			}
			if (backgroundObjects[i]["CreateMany"].GetBool())
			{
				for (int k = 0; k < backgroundObjects[i]["Amount"].GetFloat(); k++)
				{
					myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(types.at(myTypeIndex), backgroundObjects[i], k));
				}
			}
			else
			{
				myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(types.at(myTypeIndex), backgroundObjects[i]));
			}
		}
	}
	else
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: \"%s\" is missing MiddlegroundLayer\n", levelPath);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (document.HasMember("ForeGroundLayer") && document["ForeGroundLayer"].IsArray())
	{
		auto backgroundObjects = document["ForeGroundLayer"].GetArray();
		printf_s("===JSON===\n%s\n==========\n", text.c_str());
		std::vector<std::string> types;

		for (rapidjson::SizeType i = 0; i < backgroundObjects.Size(); i++)
		{
			int myTypeIndex = 0;
			bool isNewType = true;
			DebugJsonDocNonIterator(backgroundObjects[i], "ForeGroundLayer");
			for (int j = 0; j < types.size(); j++)
			{
				if (types.at(j) == backgroundObjects[i]["Type"].GetString())
				{
					myTypeIndex = j;
					isNewType = false;
					break;
				}
				myTypeIndex = j + 1;
			}
			if (isNewType)
			{
				types.push_back(backgroundObjects[i]["Type"].GetString());
				myBackgroundFactory.InitBackGroundObject(backgroundObjects[i], types.at(myTypeIndex));
			}
			if (backgroundObjects[i]["CreateMany"].GetBool())
			{
				for (int k = 0; k < backgroundObjects[i]["Amount"].GetFloat(); k++)
				{
					myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(types.at(myTypeIndex), backgroundObjects[i], k));
				}
			}
			else
			{
				myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(types.at(myTypeIndex), backgroundObjects[i]));
			}
		}
	}
	else
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: \"%s\" is missing ForeGroundLayer\n", levelPath);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}


}

void Studio::BackgroundManager::CreateTestMapBackground(float LevelWidth)
{
	myLevelWidth = 1920;
	CreateBackground(*"JSON/Background/Background_AlphaLevel.json");
}


void Studio::BackgroundManager::UpdateBackground(float aDeltaTime)
{
	for (int i = 0; i < myBackgroundObjects.size(); i++)
	{
		myBackgroundObjects.at(i)->Update(aDeltaTime);
		if (myBackgroundObjects.at(i)->GetPosition().x < -myLevelWidth)
		{

			myBackgroundObjects.at(i)->SetPosition({ myBackgroundObjects.at(i)->GetPosition().x + myLevelWidth, myBackgroundObjects.at(i)->GetPosition().y });
		}
		Studio::RendererAccessor::GetInstance()->Render(*myBackgroundObjects.at(i));
	}
}

void Studio::BackgroundManager::DebugJsonDoc(rapidjson::Value& aJsonObject, const char* aString)
{
	if (!aJsonObject[aString].HasMember("Type") && !aJsonObject[aString]["Type"].IsString())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Type or incorrectly Typed in GradientImage\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject[aString].HasMember("ImagePath") && !aJsonObject[aString]["ImagePath"].IsString())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing ImagePath or incorrectly Typed in GradientImage\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject[aString].HasMember("IsTiling") && !aJsonObject[aString]["IsTiling"].IsBool())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing IsTiling or incorrectly Typed in GradientImage\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject[aString].HasMember("IsCentered") && !aJsonObject[aString]["IsCentered"].IsBool())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing IsTiling or incorrectly Typed in GradientImage\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject[aString].HasMember("Pivot") && !aJsonObject[aString]["Pivot"]["X"].IsFloat() && !aJsonObject[aString]["Pivot"]["Y"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Pivot or incorrectly Typed in Pivot Values\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject[aString].HasMember("LayerOrder") && !aJsonObject[aString]["LayerOrder"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing LayerOrder or incorrectly Typed in LayerOrder Value\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject[aString].HasMember("Position") && !aJsonObject[aString]["Position"]["X"].IsFloat() && !aJsonObject[aString]["Position"]["Y"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s missing Position or incorrectly Typed in Position Values\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject[aString].HasMember("Scale") && !aJsonObject[aString]["Scale"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Scale or incorrectly Typed in Scale Value\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject[aString].HasMember("Speed") && !aJsonObject[aString]["Speed"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Speed or incorrectly Typed in Speed Value\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject[aString].HasMember("CreateMany") && !aJsonObject[aString]["CreateMany"].IsBool())
	{
		if (!aJsonObject[aString].HasMember("Amount") && !aJsonObject[aString]["Amount"].IsFloat())
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_RED);
			printf_s("ERROR: %s is missing Amount or incorrectly Typed in Amount Value\n", aString);
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
		}
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing CreateMany or incorrectly Typed in CreateMany Value\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject[aString].HasMember("UseRandom") && !aJsonObject[aString]["UseRandom"].IsBool())
	{
		if (!aJsonObject[aString].HasMember("RandomAtributes") && !aJsonObject[aString]["UseRandom"].IsTrue())
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_RED);
			printf_s("ERROR: %s is missing RandomAtributes\n", aString);
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
		}
		else
		{
			if (!aJsonObject[aString].HasMember("RandomPositionX") && !aJsonObject[aString]["RandomPositionX"]["X"].IsFloat() && !aJsonObject[aString]["RandomPositionX"]["Y"].IsFloat())
			{
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s is missing RandomPositionX or incorrectly Typed in Amount Value\n", aString);
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
			if (!aJsonObject[aString].HasMember("RandomPositionY") && !aJsonObject[aString]["RandomPositionY"]["X"].IsFloat() && !aJsonObject[aString]["RandomPositionY"]["Y"].IsFloat())
			{
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s  is missing RandomPositionY or incorrectly Typed in Amount Value\n", aString);
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
			if (!aJsonObject[aString].HasMember("RandomSpeed") && !aJsonObject[aString]["RandomSpeed"]["Min"].IsFloat() && !aJsonObject[aString]["RandomSpeed"]["Max"].IsFloat())
			{
				if (aJsonObject[aString]["RandomSpeed"]["Min"].GetFloat() > aJsonObject[aString]["RandomSpeed"]["Max"].GetFloat())
				{
					SETCONSOLECOLOR(CONSOLE_COLOR_RED);
					printf_s("ERROR: %s RandomSpeed Min Can not be Larger than Max\n", aString);
					SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
				}
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s is missing RandomSpeed or incorrectly Typed in Amount Value\n", aString);
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
		}
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing UseRandom or incorrectly Typed in UseRandom Value\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
}

void Studio::BackgroundManager::DebugJsonDocNonIterator(rapidjson::Value& aJsonObject, const char* aString)
{
	if (!aJsonObject.HasMember("Type") && !aJsonObject["Type"].IsString())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Type or incorrectly Typed in GradientImage\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("ImagePath") && !aJsonObject["ImagePath"].IsString())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing ImagePath or incorrectly Typed in GradientImage\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("IsTiling") && !aJsonObject["IsTiling"].IsBool())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing IsTiling or incorrectly Typed in GradientImage\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("IsCentered") && !aJsonObject["IsCentered"].IsBool())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing IsTiling or incorrectly Typed in GradientImage\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Pivot") && !aJsonObject["Pivot"]["X"].IsFloat() && !aJsonObject["Pivot"]["Y"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Pivot or incorrectly Typed in Pivot Values\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("LayerOrder") && !aJsonObject["LayerOrder"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing LayerOrder or incorrectly Typed in LayerOrder Value\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Position") && !aJsonObject["Position"]["X"].IsFloat() && !aJsonObject["Position"]["Y"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s missing Position or incorrectly Typed in Position Values\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Scale") && !aJsonObject["Scale"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Scale or incorrectly Typed in Scale Value\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Speed") && !aJsonObject["Speed"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Speed or incorrectly Typed in Speed Value\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("CreateMany") && !aJsonObject["CreateMany"].IsBool())
	{
		if (!aJsonObject.HasMember("Amount") && !aJsonObject["Amount"].IsFloat())
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_RED);
			printf_s("ERROR: %s is missing Amount or incorrectly Typed in Amount Value\n", aString);
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
		}
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing CreateMany or incorrectly Typed in CreateMany Value\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("UseRandom") && !aJsonObject["UseRandom"].IsBool())
	{
		if (!aJsonObject.HasMember("RandomAtributes") && !aJsonObject["UseRandom"].IsTrue())
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_RED);
			printf_s("ERROR: %s is missing RandomAtributes\n", aString);
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
		}
		else
		{
			if (!aJsonObject.HasMember("RandomPositionX") && !aJsonObject["RandomPositionX"]["X"].IsFloat() && !aJsonObject["RandomPositionX"]["Y"].IsFloat())
			{
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s is missing RandomPositionX or incorrectly Typed in Amount Value\n", aString);
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
			if (!aJsonObject.HasMember("RandomPositionY") && !aJsonObject["RandomPositionY"]["X"].IsFloat() && !aJsonObject["RandomPositionY"]["Y"].IsFloat())
			{
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s  is missing RandomPositionY or incorrectly Typed in Amount Value\n", aString);
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
			if (!aJsonObject.HasMember("RandomSpeed") && !aJsonObject["RandomSpeed"]["Min"].IsFloat() && !aJsonObject["RandomSpeed"]["Max"].IsFloat())
			{
				if (aJsonObject["RandomSpeed"]["Min"].GetFloat() > aJsonObject["RandomSpeed"]["Max"].GetFloat())
				{
					SETCONSOLECOLOR(CONSOLE_COLOR_RED);
					printf_s("ERROR: %s RandomSpeed Min Can not be Larger than Max\n", aString);
					SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
				}
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s is missing RandomSpeed or incorrectly Typed in Amount Value\n", aString);
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
		}
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing UseRandom or incorrectly Typed in UseRandom Value\n", aString);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
}


