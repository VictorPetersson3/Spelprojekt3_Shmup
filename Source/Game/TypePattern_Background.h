#pragma once
#include "rapidjson/document.h"
namespace Tga2D
{
	class CSprite;
}

namespace Studio
{
	class TypePattern_Background
	{
	public:
		TypePattern_Background(rapidjson::Value& aJsonObject);
		~TypePattern_Background();

		Tga2D::CSprite* GetSprite();
	private:
		Tga2D::CSprite* mySprite;
	};
}

