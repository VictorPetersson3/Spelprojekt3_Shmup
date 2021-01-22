#pragma once
#include <map>
#include "TypePattern_Background.h"

namespace Studio
{
	class BackgroundObject;
	class BackgroundFactory
	{
	public:
		BackgroundFactory() = default;
		~BackgroundFactory() = default;
		void InitBackGroundObject(rapidjson::Value& aJsonObject, const std::string& aType);
		Studio::BackgroundObject* CreateBackgroundObject(const std::string& aType, rapidjson::Value& aJsonObject);
		Studio::BackgroundObject* CreateBackgroundObject(const std::string& aType, rapidjson::Value& aJsonObject, int aIndex);
	private:
		std::map <std::string, TypePattern_Background*> myBackgroundObjects;
	};
}


