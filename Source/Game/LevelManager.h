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
	class Laser;
	class BackgroundManager;
	class EffectExplosionLarge;
	class ParticleEmitter;

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
		void SpawnBullet(const std::string& aType, VECTOR2F aPosition, const float aDamage);
		void SpawnBullet(const std::string& aType, VECTOR2F aPosition, const VECTOR2F& aDirection, const float aDamage);
		void SpawnMissile(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aExplosionRadius, const float aDamageAmount, const float aExplosionDamageAmount);
		void SpawnAOEBullet(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aRadius);
		void SpawnTimedBomb(const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aVelocity, const float aBlastRadius, const float aDamage);
		void FireLaser(bool aChoice);
		void CreateExplosionAt(const Tga2D::Vector2f& aPosition, const float aRadius = 50.0f);
		bool LevelIsCleared();
		void LoadLevel(const int aLevelIndex);
		void ReloadLevel();
		void ClearLevel();
		const int GetCurrentLevelIndex() const;
		const std::vector<std::string>& GetLevelPaths() const;

		void StopUpdating();
		void StartUpdating();

		bool IsLaserFiring();
	private:
		void UpdateEnemies();
		void LevelLogic();
		void CheckCollision();
		void CheckIfLevelIsCleared();
		void UpdateExplosions();
		void ClearEnemies();
		void ClearPacks();
		void ClearBullets();

		bool myIsUpdating = true;

		bool myLevelIsCleared;
		bool myLevelEnemiesCleared;
		bool myLevelBossSpawned;
		bool mySpawnedBoss;
		bool myHasReloaded;
		bool myHasResetShop = false;
		bool myLaserIsFiring = false;
		bool myHasStoppedLevelMusic = false;
		bool myHasParticleOnMap = false;
		int myPackIndex;
		int myCurrentLevel;
		Pack* myCurrentPack;
		Player* myPlayer = nullptr;
		Boss* myBoss = nullptr;
		Laser* myLaser = nullptr;
		BossManager* myBossManager = nullptr;
		std::vector<EffectExplosionLarge*> myExplosions;
		std::vector<Pack*> myPacks;
		std::vector<Enemy*> myEnemies;
		std::vector<Bullet*> myBullets;
		std::vector<std::string> myLevelPaths;
		BackgroundManager* myBackgroundManager;
		ParticleEmitter* myParticleEmitter;
	};
}
