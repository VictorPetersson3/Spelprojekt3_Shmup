#include "stdafx.h"
#include "EnemyFactory.h"
#include "Enemy.h"

#include <filesystem> // Hitta alla filer i ett directory
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"

Studio::EnemyFactory::~EnemyFactory()
{
	for (auto& it = myEnemyObjectTypes.begin(); it != myEnemyObjectTypes.end(); ++it)
	{
		SAFE_DELETE((*it).second);
	}
}

void Studio::EnemyFactory::InitEnemyType(rapidjson::Document& someJsonData, const std::string& aType)
{
	std::pair<std::string, Studio::TypePattern_Enemy*> temp_pair(aType, new Studio::TypePattern_Enemy(someJsonData, aType));
	myEnemyObjectTypes.insert(temp_pair);
}

Studio::Enemy* Studio::EnemyFactory::CreateEnemyObject(const std::string& aType, const Tga2D::Vector2f& aSpawnPosition)
{
	std::string type = "Default";
	for (auto types : myEnemyObjectTypes)
	{
		if (aType == types.first)
		{
			type = aType;
			break;
		}
	}
	Studio::Enemy* tempObject = new Studio::Enemy(myEnemyObjectTypes.at(type), aSpawnPosition);
	return tempObject;
}

void Studio::EnemyFactory::InitAllEnemyTypes()
{
	std::string directory = "JSON/Enemies";
	int iterator = 0;
	std::string previousPath;
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

			//Checking if it is a collission Object
			std::string pathMinusCollision = path;
			std::string pathMinusPipe = path;
			pathMinusCollision.erase(pathMinusCollision.end() - 15, pathMinusCollision.end());
			pathMinusPipe.erase(pathMinusPipe.end() -19, pathMinusPipe.end());

			if (pathMinusCollision != previousPath && pathMinusPipe != previousPath)
			{
				std::string type = path.substr(13);
				type.erase(type.end() - 5, type.end());
				InitEnemyType(document, type);
			}
			if (pathMinusPipe == previousPath)
			{
				std::string type = path.substr(13);
				type.erase(type.end() - 19, type.end());
				myEnemyObjectTypes.at(type)->CreateTurretObject(document);
			}
			if (pathMinusCollision == previousPath)
			{
				std::string type = path.substr(13);
				type.erase(type.end() - 15, type.end());
				myEnemyObjectTypes.at(type)->CreateCollissionObjects(document);
			}

			if (iterator == 0)
			{
				InitEnemyType(document, "Default");
			}
			iterator++;
			previousPath = path;
			previousPath.erase(previousPath.end() - 5, previousPath.end());
		}
	}
}

