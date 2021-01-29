#pragma once
#include "rapidjson/document.h"
#include <string>
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
		~TypePattern_Background() = default;

		const std::string& GetImagePath() const;
		const int GetAmount() const;
	private:
		std::string myImagePath;
		int myAmount;
	};
}

