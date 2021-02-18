#pragma once
#include "ButtonElement.h"
#include "Renderer.h"
#include "RendererAccessor.h"

namespace Studio
{
	class StartButton : public ButtonElement
	{
	public: 
		StartButton(const char* aSpritePath, const VECTOR2F aPosition, const VECTOR2F aSize, const VECTOR2F aPivot, const char* aTag, int aLayer,const bool aMainMenuButton);
		~StartButton();


		void Update() override;
		void OnClick() override;
		void ResetClickTimer();
		void SetLevelToLoad(const int aIndex);

		bool myIsClicked = false;

	private:
		bool myIsMainMenuStart;
		int myLevelToLoad;
		float myClickTimer;

		float mySizeTimer;
		float mySize;
	};
}