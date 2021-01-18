#pragma once
#include <vector>
namespace Studio
{
	class Pack;
	class Enemy;
	class Bullet;
	class EnemyFactory;
	class LevelManager
	{
	public:

		LevelManager();
		~LevelManager();
		void Update();
		const char* CurrentLevelPath();

		EnemyFactory* myEnemyFactory;
		void AddEnemy(Enemy* anEnemy);

	private:

		void LoadLevel(const char* aLevelPath);
		const char* myCurrentLevelPath;
		Pack* myCurrentPack;
		std::vector<Pack*> myPacks;
		std::vector<Enemy*> myEnemies;
		std::vector<Bullet*> myBullets;
	};
}
