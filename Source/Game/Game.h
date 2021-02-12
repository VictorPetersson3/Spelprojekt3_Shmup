#pragma once
#include <fstream>
#include "GameWorld.h"
#include <atomic>
#include <thread>

class CGame
{
public:
	CGame();
	~CGame();
	bool Init(const std::wstring& aVersion = L"", HWND aHWND = nullptr);
	void SetResolution(const Tga2D::Vector2ui aResolution);
	void ToggleFullScreen();
	const bool GetIsFullscreen() const;
	void Minimize();
	void ReMinimize();
private:
	void InitCallBack();
	void UpdateCallBack();
	void GamePlayThread();
	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	CGameWorld myGameWorld;
	Tga2D::Vector2ui myResolution;
	std::atomic<bool> myHasTabbed;
	std::atomic<bool> myGamePlayDone;
	std::atomic<bool> myHasSwappedBuffers;
	std::atomic<bool> myIsPlaying;
	std::atomic<bool> myHasStarted;
	std::atomic<bool> myChangeResolution;
	std::atomic<bool> myToggleFullscreen;
	std::atomic<bool> myIsFullScreen;
	std::thread myGameLogic;
};
