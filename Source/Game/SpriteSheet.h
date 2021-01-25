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

		SpriteSheet(const char* aImagePath);
		~SpriteSheet();

		// Copy constructor
		SpriteSheet(const SpriteSheet& aCopy);

		// Move constructor
		SpriteSheet(SpriteSheet&&);

		// Assignment operator
		//SpriteSheet& operator=(const SpriteSheet& aReference);

		// Move Assignment operator
		SpriteSheet& operator=(SpriteSheet&&) = delete;

		// "Private" fields
		// TODO: Give setters and getters instead
		signed int myLayer = 0;
		std::string myImagePath;
		Tga2D::CSprite* mySprite = nullptr;
		Tga2D::Vector2<float> myPosition;
		Tga2D::Vector2<float> mySize;

		// TODO: Add data used to animate this sheet
	};
}
