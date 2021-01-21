#pragma once
namespace Tga2D
{
	class CSprite;
}
namespace Studio
{
	class SpriteSheet
	{
	public:

		// "Private" fields
		// TODO: Give setters and getters instead
		signed int myLayer;
		std::string myImagePath;
		Tga2D::CSprite* mySprite;
		Tga2D::Vector2<float> myPosition;

		// TODO: Add data used to animate this sheet
	};
}
