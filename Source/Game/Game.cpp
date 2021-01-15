#include "stdafx.h"
#include <tga2d/Engine.h>
#include "Game.h"
#include <tga2d/error/error_manager.h>
#include "Timer.h"
#include "InputManager.h"

using namespace std::placeholders;

#ifdef _DEBUG
#pragma comment(lib,"TGA2D_Debug.lib")
std::wstring BUILD_NAME = L"Debug";
#endif // DEBUG
#ifdef _RELEASE
#pragma comment(lib,"TGA2D_Release.lib")
std::wstring BUILD_NAME = L"Release";
#endif // DEBUG
#ifdef _RETAIL
#pragma comment(lib,"TGA2D_Retail.lib")
std::wstring BUILD_NAME = L"Retail";
#endif // DEBUG

CGame::CGame()
{
	Studio::InputManager::Construct();
	Studio::Timer::Construct();
}


CGame::~CGame()
{
	Studio::Timer::Deconstruct();
	Studio::InputManager::Deconstruct();
	myHasStarted = false;
	myIsPlaying = false;
	myGameLogic.join();
}

LRESULT CGame::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	lParam;
	wParam;
	hWnd;
	Studio::InputManager::GetInstance()->UpdateMouseInputEvents(hWnd, message, wParam, lParam);
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		myIsPlaying = false;
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	}
	}

	return 0;
}


bool CGame::Init(const std::wstring& aVersion, HWND /*aHWND*/)
{
	Tga2D::SEngineCreateParameters createParameters;
	myGamePlayDone = false;
	myIsPlaying = true;
	myHasStarted = false;
	myHasSwappedBuffers = false;
	createParameters.myInitFunctionToCall = [this] {InitCallBack(); };
	createParameters.myWinProcCallback = [this](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {return WinProc(hWnd, message, wParam, lParam); };
	createParameters.myUpdateFunctionToCall = [this] {UpdateCallBack(); };
	createParameters.myApplicationName = L"TGA 2D " + BUILD_NAME + L"[" + aVersion + L"] ";
	unsigned short windowWidth = 1920;
	unsigned short windowHeight = 1080;
	createParameters.myWindowHeight = windowHeight;
	createParameters.myWindowWidth = windowWidth;
	//createParameters.myPreferedMultiSamplingQuality = Tga2D::EMultiSamplingQuality_High;
	createParameters.myClearColor = (Tga2D::CColor{ 0,0,0,0 });
	createParameters.myActivateDebugSystems = Tga2D::eDebugFeature_Fps |
		Tga2D::eDebugFeature_Mem |
		Tga2D::eDebugFeature_Drawcalls |
		Tga2D::eDebugFeature_Cpu |
		Tga2D::eDebugFeature_Filewatcher |
		Tga2D::eDebugFeature_OptimiceWarnings;

	myGameLogic = std::thread(&CGame::GamePlayThread, this);
	if (!Tga2D::CEngine::Start(createParameters))
	{
		ERROR_PRINT("Fatal error! Engine could not start!");
		system("pause");
		return false;
	}

	// End of program
	return true;
}

void CGame::InitCallBack()
{
	myGameWorld.Init();
	myHasStarted = true;
}

void CGame::UpdateCallBack()
{
	myGameWorld.Render();
	while (!myGamePlayDone)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
	myGameWorld.SwapBuffers();
	myGamePlayDone = false;
	myHasSwappedBuffers = true;

	if (!myIsPlaying) {
		//close application properly
	}
}

void CGame::GamePlayThread()
{
	while (myIsPlaying)
	{
		while (myHasStarted)
		{
			Studio::Timer::GetInstance()->TUpdate();
			Studio::InputManager::GetInstance()->Update();
			myGameWorld.Update(Studio::Timer::GetInstance()->TGetDeltaTime(), myIsPlaying);
			myGamePlayDone = true;
			while (!myHasSwappedBuffers)
			{
				std::this_thread::sleep_for(std::chrono::microseconds(1));
			}
			myHasSwappedBuffers = false;
			if (!myIsPlaying)
			{
				myHasStarted = true;
			}
		}
	}
}