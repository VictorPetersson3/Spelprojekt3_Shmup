#pragma once
#include "BackgroundFactory.h"

namespace Studio
{
	class BackgroundObject;
	class BackgroundManager
	{
	public:
		BackgroundManager() = default;
		~BackgroundManager() = default;

		void CreateTestMapBackground(float LevelWidth);
		void UpdateBackground(float aDeltaTime);

	private:
		BackgroundFactory myBackgroundFactory;
		std::vector<BackgroundObject*> myBackgroundObjects;
		float myLevelWidth;
	};
}


