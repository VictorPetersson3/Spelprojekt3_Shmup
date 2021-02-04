#pragma once
#include <map>
#include "TypePattern_Enemy.h"

namespace Studio
{
	class Enemy;
	class EnemyFactory
	{
	public:
		EnemyFactory() = default;
		~EnemyFactory();
		void InitEnemyType(rapidjson::Document& someJsonData, const std::string& aType);
		Studio::Enemy* CreateEnemyObject(const std::string& aType, const Tga2D::Vector2f& aSpawnPosition);

		// Loads and parses all JSON/Enemies/*.json into EnemyType
		void InitAllEnemyTypes();

	private:
		std::map<std::string, TypePattern_Enemy*> myEnemyObjectTypes;
	};
}


