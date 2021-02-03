#include "stdafx.h"
#include "BossManager.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include "rapidjson/document.h"
#include "Boss.h"

Studio::BossManager::BossManager()
{
	myCurrentBoss = 0.0f;
}

Studio::BossManager::~BossManager()
{
}

void Studio::BossManager::LoadBosses()
{
	std::string directory = "JSON/Bosses";
	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		auto filePath = entry.path().string();
		rapidjson::Document document;
		std::string text;
		std::fstream file;
		file.open(filePath);
		{
			std::string line;
			while (std::getline(file, line))
			{
				text.append(line);
			}
		}
		file.close();
		document.Parse(text.c_str());
		myBosses.push_back(new Boss("", document));
	}
}

Studio::Boss* Studio::BossManager::GetLevelBoss(int aLevelCount)
{
	return myBosses[aLevelCount];
}
