#include "stdafx.h"
#include "BackgroundManager.h"
#include "rapidjson/document.h"

// Filhantering
#include <fstream>
#include <sstream>
#include <filesystem> // Hitta alla filer i ett directory

#include "RendererAccessor.h"
#include "Renderer.h"
#include "BackgroundObject.h"

void Studio::BackgroundManager::CreateBackground(const int aLevelIndex)
{
	const char* levelPath = myLevelPaths[aLevelIndex].c_str();
	myBackgroundObjects.clear();
	rapidjson::Document document;

	std::string text;
	std::fstream file;
	file.open(levelPath);
	{
		std::string line;
		while (std::getline(file, line))
		{
			text.append(line);
			//printf("%s\n", line.c_str());
		}
	}
	file.close();
	document.Parse(text.c_str());
	//printf("Path: %s \nDocument%s", levelPath, text.c_str());
	if (document.HasMember("Json") && document["Json"].IsArray())
	{
		std::vector<std::string> myTypes;
		auto objects = document["Json"].GetArray();
		for (int i = 0; i < objects.Size(); i++)
		{
			if (objects[i].IsArray())
			{
				for (int j = 0; j < objects[i].GetArray().Size(); j++)
				{
					auto backgroundObjects = objects[i].GetArray();
					//printf_s("===JSON===\n%s\n==========\n", text.c_str());
					for (rapidjson::SizeType iterator = 0; iterator < backgroundObjects.Size(); iterator++)
					{
						int myTypeIndex = 0;
						bool isNewType = true;
						DebugJsonDocNonIterator(backgroundObjects[iterator]);
						for (int j = 0; j < myTypes.size(); j++)
						{
							if (myTypes.at(j) == backgroundObjects[iterator]["Type"].GetString())
							{
								myTypeIndex = j;
								isNewType = false;
								break;
							}
							myTypeIndex = j + 1;
						}
						if (isNewType)
						{
							myTypes.push_back(backgroundObjects[iterator]["Type"].GetString());
							myBackgroundFactory.InitBackGroundObject(backgroundObjects[iterator], myTypes.at(myTypeIndex));
						}
						if (backgroundObjects[iterator]["CreateMany"].GetBool())
						{
							for (int k = 0; k < backgroundObjects[iterator]["Amount"].GetFloat(); k++)
							{
								myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(myTypes.at(myTypeIndex), backgroundObjects[iterator], k));
							}
						}
						else
						{
							myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(myTypes.at(myTypeIndex), backgroundObjects[iterator]));
						}
					}
				}
			}
			else
			{
				//printf_s("===JSON===\n%s\n==========\n", text.c_str());
				int myTypeIndex = 0;
				bool isNewType = true;
				DebugJsonDocNonIterator(objects[i]);
				for (int j = 0; j < myTypes.size(); j++)
				{
					if (myTypes.at(j) == objects[i]["Type"].GetString())
					{
						myTypeIndex = j;
						isNewType = false;
						break;
					}
				}
				if (isNewType)
				{
					myTypes.push_back(objects[i]["Type"].GetString());
					myBackgroundFactory.InitBackGroundObject(objects[i], myTypes.at(myTypeIndex));
				}
				myBackgroundObjects.push_back(myBackgroundFactory.CreateBackgroundObject(myTypes.at(myTypeIndex), objects[i]));
			}
		}
	}
}

void Studio::BackgroundManager::Init(float LevelWidth)
{
	myLevelWidth = 1920;
	std::string directory = "JSON/Background";
	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		auto file = entry.path().string();
		std::string type = file.substr(16);
		std::string levelPathStitched = "JSON/Background/";
		levelPathStitched.append(type);
		myLevelPaths.push_back(levelPathStitched);
		printf("Level Background Path: %s\n", levelPathStitched.c_str());
	}
}

void Studio::BackgroundManager::UpdateBackground(float aDeltaTime)
{
	for (int i = 0; i < myBackgroundObjects.size(); i++)
	{
		myBackgroundObjects.at(i)->Update(aDeltaTime);
		if (myBackgroundObjects.at(i)->GetPosition().x < -myLevelWidth)
		{
			myBackgroundObjects.at(i)->SetPosition({ myBackgroundObjects.at(i)->GetPosition().x + (myLevelWidth * myBackgroundObjects.at(i)->GetTypeObject()->GetAmount()), myBackgroundObjects.at(i)->GetPosition().y });
		}
		Studio::RendererAccessor::GetInstance()->Render(*myBackgroundObjects.at(i));
	}
}

const int Studio::BackgroundManager::GetPathsSize() const
{
	return myLevelPaths.size();
}

void Studio::BackgroundManager::ClearBackground()
{
	for (int i = 0; i < myBackgroundObjects.size(); i++)
	{
		SAFE_DELETE(myBackgroundObjects[i]);
	}
	myBackgroundObjects.clear();
}

void Studio::BackgroundManager::DebugJsonDoc(rapidjson::Value& aJsonObject, const int aIterator)
{
	if (!aJsonObject.HasMember("Type") && !aJsonObject["Type"].IsString())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: Item nr %i is missing Type or incorrectly Typed in GradientImage\n", aIterator);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("ImagePath") && !aJsonObject["ImagePath"].IsString())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: Item nr %i is missing ImagePath or incorrectly Typed in GradientImage\n", aIterator);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("IsTiling") && !aJsonObject["IsTiling"].IsBool())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: Item nr %i is missing IsTiling or incorrectly Typed in GradientImage\n", aIterator);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("IsCentered") && !aJsonObject["IsCentered"].IsBool())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing IsTiling or incorrectly Typed in GradientImage\n", aIterator);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Pivot") && !aJsonObject["Pivot"]["X"].IsFloat() && !aJsonObject["Pivot"]["Y"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Pivot or incorrectly Typed in Pivot Values\n", aIterator);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("LayerOrder") && !aJsonObject["LayerOrder"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing LayerOrder or incorrectly Typed in LayerOrder Value\n", aIterator);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Position") && !aJsonObject["Position"]["X"].IsFloat() && !aJsonObject["Position"]["Y"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s missing Position or incorrectly Typed in Position Values\n", aIterator);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Scale") && !aJsonObject["Scale"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Scale or incorrectly Typed in Scale Value\n", aIterator);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Speed") && !aJsonObject["Speed"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Speed or incorrectly Typed in Speed Value\n", aIterator);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("CreateMany") && !aJsonObject["CreateMany"].IsBool())
	{
		if (!aJsonObject.HasMember("Amount") && !aJsonObject["Amount"].IsFloat())
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_RED);
			printf_s("ERROR: %s is missing Amount or incorrectly Typed in Amount Value\n", aIterator);
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
		}
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing CreateMany or incorrectly Typed in CreateMany Value\n", aIterator);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("UseRandom") && !aJsonObject["UseRandom"].IsBool())
	{
		if (!aJsonObject.HasMember("RandomAtributes") && !aJsonObject["UseRandom"].IsTrue())
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_RED);
			printf_s("ERROR: %s is missing RandomAtributes\n", aIterator);
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
		}
		else
		{
			if (!aJsonObject.HasMember("RandomPositionX") && !aJsonObject["RandomPositionX"]["X"].IsFloat() && !aJsonObject["RandomPositionX"]["Y"].IsFloat())
			{
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s is missing RandomPositionX or incorrectly Typed in Amount Value\n", aIterator);
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
			if (!aJsonObject.HasMember("RandomPositionY") && !aJsonObject["RandomPositionY"]["X"].IsFloat() && !aJsonObject["RandomPositionY"]["Y"].IsFloat())
			{
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s  is missing RandomPositionY or incorrectly Typed in Amount Value\n", aIterator);
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
			if (!aJsonObject.HasMember("RandomSpeed") && !aJsonObject["RandomSpeed"]["Min"].IsFloat() && !aJsonObject["RandomSpeed"]["Max"].IsFloat())
			{
				if (aJsonObject["RandomSpeed"]["Min"].GetFloat() > aJsonObject["RandomSpeed"]["Max"].GetFloat())
				{
					SETCONSOLECOLOR(CONSOLE_COLOR_RED);
					printf_s("ERROR: %s RandomSpeed Min Can not be Larger than Max\n", aIterator);
					SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
				}
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s is missing RandomSpeed or incorrectly Typed in Amount Value\n", aIterator);
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
		}
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing UseRandom or incorrectly Typed in UseRandom Value\n", aIterator);
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
}

void Studio::BackgroundManager::DebugJsonDocNonIterator(rapidjson::Value& aJsonObject)
{
	if (!aJsonObject.HasMember("Type") && !aJsonObject["Type"].IsString())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Type or incorrectly Typed in GradientImage\n");
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("ImagePath") && !aJsonObject["ImagePath"].IsString())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing ImagePath or incorrectly Typed in GradientImage\n");
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("IsTiling") && !aJsonObject["IsTiling"].IsBool())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing IsTiling or incorrectly Typed in GradientImage\n");
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("IsCentered") && !aJsonObject["IsCentered"].IsBool())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing IsTiling or incorrectly Typed in GradientImage\n");
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Pivot") && !aJsonObject["Pivot"]["X"].IsFloat() && !aJsonObject["Pivot"]["Y"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Pivot or incorrectly Typed in Pivot Values\n");
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("LayerOrder") && !aJsonObject["LayerOrder"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing LayerOrder or incorrectly Typed in LayerOrder Value\n");
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Position") && !aJsonObject["Position"]["X"].IsFloat() && !aJsonObject["Position"]["Y"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s missing Position or incorrectly Typed in Position Values\n");
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Scale") && !aJsonObject["Scale"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Scale or incorrectly Typed in Scale Value\n");
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("Speed") && !aJsonObject["Speed"].IsFloat())
	{
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing Speed or incorrectly Typed in Speed Value\n");
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("CreateMany") && !aJsonObject["CreateMany"].IsBool())
	{
		if (!aJsonObject.HasMember("Amount") && !aJsonObject["Amount"].IsFloat())
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_RED);
			printf_s("ERROR: %s is missing Amount or incorrectly Typed in Amount Value\n");
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
		}
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing CreateMany or incorrectly Typed in CreateMany Value\n");
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
	if (!aJsonObject.HasMember("UseRandom") && !aJsonObject["UseRandom"].IsBool())
	{
		if (!aJsonObject.HasMember("RandomAtributes") && !aJsonObject["UseRandom"].IsTrue())
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_RED);
			printf_s("ERROR: %s is missing RandomAtributes\n");
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
		}
		else
		{
			if (!aJsonObject.HasMember("RandomPositionX") && !aJsonObject["RandomPositionX"]["X"].IsFloat() && !aJsonObject["RandomPositionX"]["Y"].IsFloat())
			{
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s is missing RandomPositionX or incorrectly Typed in Amount Value\n");
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
			if (!aJsonObject.HasMember("RandomPositionY") && !aJsonObject["RandomPositionY"]["X"].IsFloat() && !aJsonObject["RandomPositionY"]["Y"].IsFloat())
			{
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s  is missing RandomPositionY or incorrectly Typed in Amount Value\n");
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
			if (!aJsonObject.HasMember("RandomSpeed") && !aJsonObject["RandomSpeed"]["Min"].IsFloat() && !aJsonObject["RandomSpeed"]["Max"].IsFloat())
			{
				if (aJsonObject["RandomSpeed"]["Min"].GetFloat() > aJsonObject["RandomSpeed"]["Max"].GetFloat())
				{
					SETCONSOLECOLOR(CONSOLE_COLOR_RED);
					printf_s("ERROR: %s RandomSpeed Min Can not be Larger than Max\n");
					SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
				}
				SETCONSOLECOLOR(CONSOLE_COLOR_RED);
				printf_s("ERROR: %s is missing RandomSpeed or incorrectly Typed in Amount Value\n");
				SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
			}
		}
		SETCONSOLECOLOR(CONSOLE_COLOR_RED);
		printf_s("ERROR: %s is missing UseRandom or incorrectly Typed in UseRandom Value\n");
		SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
	}
}


