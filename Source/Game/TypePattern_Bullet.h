#pragma once


namespace Tga2D
{
	class CSprite;
}

namespace Studio
{
	class TypePattern_Bullet
	{
	public:
		TypePattern_Bullet(const std::string& aPath);
		~TypePattern_Bullet() = default;
		std::shared_ptr<Tga2D::CSprite> GetSprite();
	private:
		std::shared_ptr<Tga2D::CSprite> mySprite;
	};
}


