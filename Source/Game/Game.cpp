#include "stdafx.h"
#include <tga2d/Engine.h>
#include "Game.h"
#include <tga2d/error/error_manager.h>
#include "Timer.h"
#include "InputManager.h"
#include "Game_Accessor.h"
#include "wtypes.h"
#include "MenuManagerSingleton.h"

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
	myResolution = { 0, 0 };
	myChangeResolution = false;
	myToggleFullscreen = false;
	myIsFullScreen = false;
	Studio::GameAccessor::GetInstance().SetGame(this);
}


CGame::~CGame()
{
	Studio::Timer::Deconstruct();
	Studio::InputManager::Deconstruct();
	myHasStarted = false;
	myIsPlaying = false;
	myHasSwappedBuffers = true;
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
	createParameters.myRenderWidth = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myWindowHeight = windowHeight;
	createParameters.myWindowWidth = windowWidth;
	//createParameters.myWindowSetting = Tga2D::EWindowSetting::EWindowSetting_Borderless;
	//createParameters.myPreferedMultiSamplingQuality = Tga2D::EMultiSamplingQuality_High;
	//createParameters.myStartInFullScreen = true;
	createParameters.myClearColor = (Tga2D::CColor{ 0,0,0,0 });
	createParameters.myUseLetterboxAndPillarbox = true;
	createParameters.myActivateDebugSystems = Tga2D::eDebugFeature_Fps |
		Tga2D::eDebugFeature_Mem |
		Tga2D::eDebugFeature_Drawcalls |
		Tga2D::eDebugFeature_Cpu |
		Tga2D::eDebugFeature_Filewatcher |
		Tga2D::eDebugFeature_OptimiceWarnings;
	myHasTabbed = false;
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

void CGame::SetResolution(const Tga2D::Vector2ui aResolution)
{
	myResolution = aResolution;
	myChangeResolution = true;
}

void CGame::ToggleFullScreen()
{
	myIsFullScreen = !myIsFullScreen;
	myToggleFullscreen = true;
}

const bool CGame::GetIsFullscreen() const
{
	return myIsFullScreen;
}

void CGame::Minimize()
{
	Tga2D::CEngine::GetInstance()->Minimize();
}

void CGame::ReMinimize()
{
	Tga2D::CEngine::GetInstance()->ReMinimize();
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
	if (GetActiveWindow() != GetForegroundWindow())
	{
		myHasTabbed = true;
		//if (!Studio::Timer::GetInstance()->IsFrozen())
		//{
		//	Studio::Timer::GetInstance()->Freeze();
		//}
		//Studio::GameAccessor::GetInstance().GetGame()->Minimize();
	}
	if (myHasTabbed && GetActiveWindow() == GetForegroundWindow())
	{
		//Studio::GameAccessor::GetInstance().GetGame()->ReMinimize();
		if (myIsFullScreen)
		{
			//Tga2D::CEngine::GetInstance()->SetFullScreen(myIsFullScreen);
		}
		Studio::MenuManagerSingleton::GetInstance()->ResetButtonColliders();
		myHasTabbed = false;
	}
	if (myChangeResolution)
	{
		Tga2D::CEngine::GetInstance()->SetResolution(myResolution, true);
		myChangeResolution = false;
	}
	if (myToggleFullscreen)
	{
		Tga2D::CEngine::GetInstance()->SetFullScreen(myIsFullScreen);
		printf("Game SetFullscreen\n");
		myToggleFullscreen = false;
		myChangeResolution = true;
	}
	
	myGamePlayDone = false;
	myHasSwappedBuffers = true;
}

void CGame::GamePlayThread()
{
	while (myIsPlaying)
	{
		while (myHasStarted)
		{
			Studio::Timer::GetInstance()->TUpdate();
			Studio::InputManager::GetInstance()->Update();
			myGameWorld.Update(Studio::Timer::GetInstance()->TGetDeltaTime(), myIsPlaying, myHasTabbed);
			myGamePlayDone = true;
			while (!myHasSwappedBuffers)
			{
				std::this_thread::sleep_for(std::chrono::microseconds(1));
			}
			myHasSwappedBuffers = false;
		}
	}
}