#pragma once
#include <vector>
namespace Studio
{
	class Enemy;
	class Bullet;
	class Player;
	class LevelManager
	{
	public:

		LevelManager();
		~LevelManager();
		void Update();

	private:

		void LoadLevel(const char* aLevelPath);
		std::vector<Enemy*> myEnemes;
		std::vector<Bullet*> myBullets;
	};
}
