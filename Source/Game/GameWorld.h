#pragma once
#include "Renderer.h"
#include "BackgroundManager.h"
#include <vector>

namespace Studio
{
	class Player;
	class Enemy;
	class LevelManager;
	class MenuManager;
}
namespace Tga2D
{
	class CSprite;
	class FBXModel;
	class CAudio;
}

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init();
	void Update(float aDeltaTime, std::atomic<bool>& aIsPlaying);
	void Render();
	void SwapBuffers();
private:
	void CheckIfEnemiesHit();
private:
	Studio::BackgroundManager myBackgroundManager;
	Renderer myRenderer;
	Tga2D::CSprite* myTga2dLogoSprite;
	Studio::Player* myPlayer;

	Studio::MenuManager* myMenuManager;

	Studio::LevelManager* myLevelManager;
	std::vector<Studio::Enemy*> myEnemies;
};