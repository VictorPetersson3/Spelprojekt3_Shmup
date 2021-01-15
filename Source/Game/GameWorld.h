#pragma once
#include "Renderer.h"
#include "BackgroundManager.h"
#include <vector>

namespace Studio
{
	class Player;
	class Enemy;
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
	Studio::BackgroundManager myBackgroundManager;
	Renderer myRenderer;
	Tga2D::CSprite* myTga2dLogoSprite;
	Studio::Player* myPlayer;

	std::vector<Studio::Enemy*> myEnemies;
};