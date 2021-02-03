#include "stdafx.h"
#include "EnemyFactory.h"
#include "Enemy.h"

#include <filesystem> // Hitta alla filer i ett directory
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"

Studio::EnemyFactory::~EnemyFactory()
{
	/*using enemyMap = std::map<std::string, TypePattern_Enemy*>;
	for (enemyMap::iterator it = myEnemyObjects.begin();
		it != myEnemyObjects.end(); it++)
	{
		auto& value = it->second;
		SAFE_DELETE(value);
	}*/
	for (auto it = myEnemyObjects.begin(); it != myEnemyObjects.end(); ++it)
	{
		delete (*it).second;
		SAFE_DELETE((*it).second);
	}
}

void Studio::EnemyFactory::InitEnemyType(rapidjson::Document& someJsonData, const std::string& aType)
{
	std::pair<std::string, Studio::TypePattern_Enemy*> temp_pair(aType, new Studio::TypePattern_Enemy(someJsonData, aType));
	myEnemyObjects.insert(temp_pair);
}

Studio::Enemy* Studio::EnemyFactory::CreateEnemyObject(const std::string& aType, const Tga2D::Vector2f& aSpawnPosition)
{
	std::string type = "Default";
	for (auto types : myEnemyObjects)
	{
		if (aType == types.first)
		{
			type = aType;
			break;
		}
	}
	Studio::Enemy* tempObject = new Studio::Enemy(myEnemyObjects.at(type), aSpawnPosition);
	return tempObject;
}

void Studio::EnemyFactory::InitAllEnemyTypes()
{
	std::string directory = "JSON/Enemies";
	int iterator = 0;
	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		auto file = entry.path().string();
		printf_s("File %s\n", file.c_str());
		
		if (entry.path().extension().string() == ".json")
		{
			auto path = entry.path().string();

			rapidjson::Document document;
			std::string text;
			std::fstream file;
			file.open(path);
			{
				std::string line;
				while (std::getline(file, line))
				{
					text.append(line);
				}
			}
			file.close();
			document.Parse(text.c_str());

			std::string type = path.substr(13);
			type.erase(type.end()-5, type.end());
			if (iterator == 0)
			{
				InitEnemyType(document, "Default");
			}
			InitEnemyType(document, type);
		}
	}
}

