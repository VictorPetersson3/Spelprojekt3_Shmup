#pragma once


namespace Studio
{
	class Enemy;
	class TypePattern_Enemy;
	class SpriteSheet;
	class TurretPipe
	{
	public:
		TurretPipe(Enemy* aEnemyPointer, TypePattern_Enemy* aTypePatternEnemy);
		~TurretPipe();
		void Update(); 
	private:
		float myShootTimer;
		float myPipeLength;
		SpriteSheet* mySpriteSheet;
		Enemy* myEnemy;
		TypePattern_Enemy* myEnemyType;
		Tga2D::Vector2f myPosition;
		Tga2D::Vector2f myTurretDirection;
	};
}


