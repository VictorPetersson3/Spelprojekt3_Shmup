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

		LevelManager(BackgroundManager* aBackgroundManager);
		~LevelManager();
		void Update(Player* aPlayer);
		const std::string& CurrentLevelPath();

		EnemyFactory* myEnemyFactory;
		BulletFactory* myBulletFactory;
		
		void AddEnemy(Enemy* anEnemy);
		void SpawnBullet(const std::string& aType, VECTOR2F aPosition);
		void SpawnMissile(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition);
		void SpawnAOEBullet(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aRadius);
		bool LevelIsCleared();
		void LoadLevel(const int aLevelIndex);
		void ReloadLevel();
		const int GetCurrentLevelIndex() const;
		const std::vector<std::string>& GetLevelPaths() const;

	private:
		void LevelLogic();
		void CheckCollision();
		void CheckIfLevelIsCleared();
		void UpdateExplosions();

		bool myLevelIsCleared;
		bool myLevelEnemiesCleared;
		bool myLevelBossSpawned;
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
