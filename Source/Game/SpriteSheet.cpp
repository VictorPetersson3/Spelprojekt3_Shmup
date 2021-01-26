#include "stdafx.h"
#include "SpriteSheet.h"
#include <tga2d/sprite/sprite.h>
namespace Studio
{
	SpriteSheet::SpriteSheet(const char* aImagePath)
	{
		SAFE_CREATE(mySprite, Tga2D::CSprite(aImagePath));
		mySprite->SetPivot({ 0.5f, 0.5f });

		if (aImagePath != nullptr)
		{
			mySize = mySprite->GetImageSize();
		}
		else
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_WARNING);
			printf_s("SpriteSheet: ImagePath was nullptr, setting it to debugpixel and its size to 100x100\n");
			SETCONSOLECOLOR(CONSOLE_COLOR_NORMAL);

			myImagePath = "debugpixel";
			mySize = { 100.0f, 100.0f };
		}
	}

	SpriteSheet::~SpriteSheet()
	{
		SAFE_DELETE(mySprite);
	}

	// Copy Constructor
	SpriteSheet::SpriteSheet(const SpriteSheet& aCopy)
	{
		myLayer = aCopy.myLayer;
		myImagePath = aCopy.myImagePath;
		myPosition = aCopy.myPosition;
		mySize = aCopy.mySize;

		mySprite = new Tga2D::CSprite(*aCopy.mySprite);
	}

	// Move Constructor
	SpriteSheet::SpriteSheet(SpriteSheet&& aCopy)
	{
		myLayer = aCopy.myLayer;
		myImagePath = aCopy.myImagePath;
		myPosition = aCopy.myPosition;
		mySize = aCopy.mySize;

		mySprite = aCopy.mySprite;
		aCopy.mySprite = nullptr;
	}
}
