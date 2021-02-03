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

		void CreateBackground(const char* aLevelPath);
		void Init(float LevelWidth);
		void UpdateBackground(float aDeltaTime);

	private:
		std::vector<std::string> myLevelpaths;
		BackgroundFactory myBackgroundFactory;
		std::vector<BackgroundObject*> myBackgroundObjects;
		void DebugJsonDoc(rapidjson::Value& aJsonObject, const int aIterator);
		void DebugJsonDocNonIterator(rapidjson::Value& aJsonObject);
		float myLevelWidth = 1920;
	};
}


