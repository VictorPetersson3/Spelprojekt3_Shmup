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

void Studio::EnemyFactory::InitEnemyType(const std::string& aPath, const unsigned int aLayerOrder, const std::string& aType)
{
	std::pair<std::string, Studio::TypePattern_Enemy*> temp_pair(aType, new Studio::TypePattern_Enemy(aPath, aLayerOrder));
	myEnemyObjects.insert(temp_pair);
}

Studio::Enemy* Studio::EnemyFactory::CreateEnemyObject(const std::string& aType, const Tga2D::Vector2f& aPosition)
{
	Studio::Enemy* tempObject = new Studio::Enemy(myEnemyObjects.at(aType)->GetSprite(), aPosition);
	return tempObject;
}

void Studio::EnemyFactory::InitAllEnemyTypes()
{
	std::string directory = "JSON/Enemies";
	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		auto file = entry.path().string();
		printf_s("File %s", file.c_str());

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
		}
	}
}

