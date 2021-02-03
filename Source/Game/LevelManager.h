#pragma once
#include "Enums.h"
#include <vector>
namespace Studio
{
	class Pack;
	class Enemy;
	class Bullet;
	class Player;
	class EnemyFactory;
	class BulletFactory;
	class Boss;
	class BossManager;
	
	class LevelManager
	{
	public:

		LevelManager();
		~LevelManager();
		void Update(Player* aPlayer);
		const std::string& CurrentLevelPath();

		EnemyFactory* myEnemyFactory;
		BulletFactory* myBulletFactory;
		
		void AddEnemy(Enemy* anEnemy);
		void SpawnBullet(const std::string& aType, VECTOR2F aPosition);
		bool LevelIsCleared();
		void LoadLevel(const int aLevelIndex);
		const std::string& GetCurrentLevelPath() const;

	private:
		void LevelLogic();
		void CheckCollision();
		void CheckIfLevelIsCleared();

		bool myLevelIsCleared;
		bool myLevelEnemiesCleared;
		bool myLevelBossSpawned;
		int myPackIndex;
		Pack* myCurrentPack;
		Player* myPlayer = nullptr;
		Boss* myBoss = nullptr;
		BossManager* myBossManager = nullptr;
		std::vector<Pack*> myPacks;
		std::vector<Enemy*> myEnemies;
		std::vector<Bullet*> myBullets;

		std::string myCurrentLevelPath;
		std::vector<std::string> myLevelPaths;
	};
}
