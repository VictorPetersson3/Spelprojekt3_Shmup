#pragma once
#include <vector>
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
		void InitBackGroundObject(const std::string& aPath, const unsigned int aLayerOrder, const std::string& aType);
		Studio::BackgroundObject* CreateBackgroundObject(const std::string& aType, const Tga2D::Vector2f& aPosition, float aSpeed);
		Studio::BackgroundObject* CreateBackgroundObject(const std::string& aType, const Tga2D::Vector2f& aPosition, float aSpeed, const Tga2D::Vector2f& aSize);
	private:
		std::map <std::string, TypePattern_Background*> myBackgroundObjects;
	};
}


