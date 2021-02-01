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
		void InitEnemyType(const std::string& aPath, const unsigned int aLayerOrder, const std::string& aType);
		Studio::Enemy* CreateEnemyObject(const std::string& aType, const Tga2D::Vector2f& aPosition);

		// Loads and parses all JSON/Enemies/*.json into EnemyType
		void InitAllEnemyTypes();

	private:
		std::map<std::string, TypePattern_Enemy*> myEnemyObjects;
	};
}


