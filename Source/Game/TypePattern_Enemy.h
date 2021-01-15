#pragma once

namespace Tga2D
{
	class CSprite;
}
namespace Studio
{
	class TypePattern_Enemy
	{
	public:
		TypePattern_Enemy(const std::string& aPath, const unsigned int aLayerOrder);
		~TypePattern_Enemy();

		const unsigned int GetLayerOrder() const;
		Tga2D::CSprite* GetSprite();
	private:
		Tga2D::CSprite* mySprite;
		const unsigned int myLayerOrder;
	};
}


