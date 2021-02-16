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
	class ScoreManager;
	class CoinManager;
	class Score;
	class AudioManager;
	class Player_JsonParser;
	class VideoPlayer;
	class MousePointer;
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
	void Update(float aDeltaTime, std::atomic<bool>& aIsPlaying, bool aHasTabbed);
	void Render();
	void SwapBuffers();
private:
	void InputStuff();
	bool myHasStarted;

	Studio::BackgroundManager myBackgroundManager;
	Renderer myRenderer;
	Tga2D::CSprite* myTga2dLogoSprite;
	Studio::Player* myPlayer;

	Studio::MenuManager* myMenuManager;

	Studio::ScoreManager* myScoreManager;

	Studio::AudioManager* myAudioManager;

	Studio::CoinManager* myCoinManager;

	Studio::LevelManager* myLevelManager;
	std::vector<Studio::Enemy*> myEnemies;
	Studio::Player_JsonParser* myPlayerData;

	Studio::VideoPlayer* myVideoPlayer;
	
	Studio::MousePointer* myMousePointer;
};
