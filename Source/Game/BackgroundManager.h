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

		void CreateBackground(const int aLevelIndex);
		void Init(float LevelWidth);
		void UpdateBackground(float aDeltaTime);
		const int GetPathsSize() const;

	private:
		std::vector<std::string> myLevelPaths;
		BackgroundFactory myBackgroundFactory;
		std::vector<BackgroundObject*> myBackgroundObjects;
		void DebugJsonDoc(rapidjson::Value& aJsonObject, const int aIterator);
		void DebugJsonDocNonIterator(rapidjson::Value& aJsonObject);
		float myLevelWidth = 1920;
	};
}


