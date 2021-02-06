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
	class BackgroundManager;
	class EffectExplosionLarge;
	
	class LevelManager
	{
	public:

		LevelManager(BackgroundManager* aBackgroundManager, Player* aPlayer);
		~LevelManager();
		void Update();
		const std::string& CurrentLevelPath();

		EnemyFactory* myEnemyFactory;
		BulletFactory* myBulletFactory;
		
		void AddEnemy(Enemy* anEnemy);
		void SpawnBullet(const std::string& aType, VECTOR2F aPosition);
		void SpawnBullet(const std::string& aType, VECTOR2F aPosition, const VECTOR2F& aDirection);
		void SpawnMissile(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aDirection);
		void SpawnAOEBullet(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aRadius);
		bool LevelIsCleared();
		void LoadLevel(const int aLevelIndex);
		void ReloadLevel();
		void ClearLevel();
		const int GetCurrentLevelIndex() const;
		const std::vector<std::string>& GetLevelPaths() const;

	private:
		void UpdateEnemies();
		void LevelLogic();
		void CheckCollision();
		void CheckIfLevelIsCleared();
		void UpdateExplosions();
		void ClearEnemies();
		void ClearPacks();
		void ClearBullets();


		bool myLevelIsCleared;
		bool myLevelEnemiesCleared;
		bool myLevelBossSpawned;
		bool mySpawnedBoss;
		bool myHasReloaded;
		int myPackIndex;
		int myCurrentLevel;
		Pack* myCurrentPack;
		Player* myPlayer = nullptr;
		Boss* myBoss = nullptr;
		BossManager* myBossManager = nullptr;
		std::vector<EffectExplosionLarge*> myExplosions;
		std::vector<Pack*> myPacks;
		std::vector<Enemy*> myEnemies;
		std::vector<Bullet*> myBullets;
		std::vector<std::string> myLevelPaths;
		BackgroundManager* myBackgroundManager;
	};
}
