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

			myImagePath = "sprites/debugpixel.dds";
			mySize = { 100.0f, 100.0f };
		}
	}

	SpriteSheet::SpriteSheet(const char* aImagePath, const Tga2D::Vector2f& aAmountOfFrames, const Tga2D::Vector2f& aPivot)
	{
		SAFE_CREATE(mySprite, Tga2D::CSprite(aImagePath));
		mySprite->SetPivot(aPivot);

		if (aImagePath != nullptr)
		{
			mySize = mySprite->GetImageSize();
			myImagePath = aImagePath;
		}
		else
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_WARNING);
			printf_s("SpriteSheet: ImagePath was nullptr, setting it to debugpixel and its size to 100x100\n");
			SETCONSOLECOLOR(CONSOLE_COLOR_NORMAL);

			myImagePath = "debugpixel";
			mySize = { 100.0f, 100.0f };
		}
		myRectSize.x = (static_cast<float>(mySprite->GetImageSize().x) / aAmountOfFrames.x) / static_cast<float>(mySprite->GetImageSize().x);
		myRectSize.y = (static_cast<float>(mySprite->GetImageSize().y) / aAmountOfFrames.y) / static_cast<float>(mySprite->GetImageSize().y);
		mySprite->SetTextureRect(myRectSize.x - myRectSize.x, myRectSize.y - myRectSize.y, myRectSize.x, myRectSize.y);
		mySize.x = static_cast<float>(mySprite->GetImageSize().x / aAmountOfFrames.x);
		mySize.y = static_cast<float>(mySprite->GetImageSize().y / aAmountOfFrames.y);
		//mySprite->SetSizeRelativeToImage({ (myRectSize.x / static_cast<float>(mySprite->GetImageSize().x)), (myRectSize.y / static_cast<float>(mySprite->GetImageSize().y)) });
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
		myRectSize = aCopy.myRectSize;

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
	void SpriteSheet::UpdateAnimation(const Tga2D::Vector2f& aCurrentFrame)
	{
		mySprite->SetTextureRect(
			myRectSize.x * aCurrentFrame.x - myRectSize.x,	//TopLeftX Current Frame
			myRectSize.y * aCurrentFrame.y - myRectSize.y,	//TopLeftY Current Frame
			myRectSize.x * aCurrentFrame.x,		//BotLeftX Current Frame
			myRectSize.y * aCurrentFrame.y);	//BotLeftY Current Frame
	}
}
