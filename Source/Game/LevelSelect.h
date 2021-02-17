#pragma once
#include "MenuObject.h"

namespace Studio
{
	class GenericButton;
	class MenuManager;
	class ImageElement;
	class LevelSelect : public MenuObject
	{
	public:
		LevelSelect(MenuManager* aMenuManager);
		~LevelSelect();
		void Update();
		void Enable();
		void Disable();
		void RecalcColliders();
	private:
		bool myIsActive;
		GenericButton* myLevel1Button;
		GenericButton* myLevel2Button;
		GenericButton* myLevel3Button;
		GenericButton* myTutorialButton;
		ImageElement* myMainMenuBackground;

		GenericButton* myBackButton;
		MenuManager* myMenuManager;
	};
}