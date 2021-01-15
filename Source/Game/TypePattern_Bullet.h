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
		TypePattern_Bullet(const std::string& aPath, const unsigned int aLayerOrder);
		~TypePattern_Bullet();

		const unsigned int GetLayerOrder() const;
		Tga2D::CSprite* GetSprite();
	private:
		Tga2D::CSprite* mySprite;
		const unsigned int myLayerOrder;
	};
}


