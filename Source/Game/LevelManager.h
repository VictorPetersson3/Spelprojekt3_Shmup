#pragma once
#include <vector>
namespace Studio
{
	class Pack;
	class Enemy;
	class Bullet;
	class EnemyFactory;
	class Player;
	class LevelManager
	{
	public:

		LevelManager(Player* aPlayer);
		~LevelManager();
		void Update();
		const char* CurrentLevelPath();

		EnemyFactory* myEnemyFactory;
		
		void AddEnemy(Enemy* anEnemy);

	private:

		void LoadLevel(const char* aLevelPath);
		const char* myCurrentLevelPath;
		Pack* myCurrentPack;
		Player* myPlayer;
		std::vector<Pack*> myPacks;
		std::vector<Enemy*> myEnemies;
		std::vector<Bullet*> myBullets;
	};
}
