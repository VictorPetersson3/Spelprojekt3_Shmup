#pragma once
#include "MenuObject.h"

namespace Studio
{
	class GenericButton;
	class MenuManager;
	class ImageElement;
	class Options : public MenuObject
	{
	public:
		Options(MenuManager* aMenuManager);
		~Options();
		void Update();
		void Enable();
		void Disable();
		void RecalcColliders();
	private:
		bool myIsActive;
		bool myHasStarted;
		float myClickTimer;
		GenericButton* myToggleFullScreenOff;
		GenericButton* myToggleFullScreenOn;
		GenericButton* my640x360;
		GenericButton* my960x540;
		GenericButton* my1280x720;
		GenericButton* my1600x900;
		GenericButton* my1920x1080;
		GenericButton* my2560x1440;
		
		ImageElement* myMainMenuBackground;
		ImageElement* myResolutionImageElement;
		ImageElement* myFullscreenText;
		MenuManager* myMenuManager;
	};
};

