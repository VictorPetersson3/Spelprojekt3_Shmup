#include "stdafx.h"
#include "EnemyFactory.h"
#include "Enemy.h"

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