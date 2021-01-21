#pragma once
#include <vector>
namespace Studio
{
	class Pack;
	class Enemy;
	class Bullet;
	class Player;
	class EnemyFactory;
	class LevelManager
	{
	public:

		LevelManager();
		~LevelManager();
		void Update(Player* aPlayer);
		const char* CurrentLevelPath();

		EnemyFactory* myEnemyFactory;
		
		void AddEnemy(Enemy* anEnemy);
		bool LevelIsCleared();
		void LoadLevel(const char* aLevelPath);
		const char* GetCurrentLevelPath() const;

	private:
		void LevelLogic();
		void CheckCollision();
		void CheckIfLevelIsCleared();
		bool myLevelIsCleared;
		const char* myCurrentLevelPath;
		int myPackIndex;
		Pack* myCurrentPack;
		Player* myPlayer = nullptr;
		std::vector<Pack*> myPacks;
		std::vector<Enemy*> myEnemies;
		std::vector<Bullet*> myBullets;
	};
}
