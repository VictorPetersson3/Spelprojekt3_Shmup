#include "stdafx.h"
#include "SpriteSheet.h"
#include <tga2d/sprite/sprite.h>
#include <string>
namespace Studio
{
	SpriteSheet::SpriteSheet(const char* aImagePath)
	{
		// add type check for ImagePath???
		//std::string path = "Sprites/";
		//path.append(aImagePath).append(".dds").c_str();

		SAFE_CREATE(mySprite, Tga2D::CSprite(aImagePath));
		mySprite->SetPivot({ 0.5f, 0.5f });
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

			myImagePath = "sprites/debugpixel.dds";
			mySize = { 100.0f, 100.0f };
		}
	}

	SpriteSheet::SpriteSheet(const char* aImagePath, const Tga2D::Vector2f& aAmountOfFrames) :
		SpriteSheet(aImagePath)
	{
		myRectSize.x = (mySize.x / aAmountOfFrames.x) / mySize.x;
		myRectSize.y = (mySize.y / aAmountOfFrames.y) / mySize.y;
		mySprite->SetTextureRect(myRectSize.x - myRectSize.x, myRectSize.y - myRectSize.y, myRectSize.x, myRectSize.y);
		mySize.x = mySize.x / aAmountOfFrames.x;
		mySize.y = mySize.y / aAmountOfFrames.y;
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
	Tga2D::Vector2<float>& SpriteSheet::GetSize()
	{
		return mySize;
	}
	Tga2D::Vector2<float>& SpriteSheet::GetPosition()
	{
		return myPosition;
	}
	Tga2D::CSprite* SpriteSheet::GetSprite()
	{
		return mySprite;
	}
	const std::string& SpriteSheet::GetImagePath() const
	{
		return myImagePath;
	}
	const int SpriteSheet::GetLayer() const
	{
		return myLayer;
	}
	void SpriteSheet::SetAmountOfFrames(const Tga2D::Vector2f& aAmountOfFrames)
	{
		myRectSize.x = (mySize.x / aAmountOfFrames.x) / mySize.x;
		myRectSize.y = (mySize.y / aAmountOfFrames.y) / mySize.y;
		mySprite->SetTextureRect(myRectSize.x - myRectSize.x, myRectSize.y - myRectSize.y, myRectSize.x, myRectSize.y);
		mySize.x = mySize.x / aAmountOfFrames.x;
		mySize.y = mySize.y / aAmountOfFrames.y;
	}
	void SpriteSheet::SetPosition(const Tga2D::Vector2f& aPos)
	{
		myPosition = aPos;
	}
	void SpriteSheet::SetLayer(signed int aLayer)
	{
		myLayer = aLayer;
	}
	
	void SpriteSheet::SetImagePath(const std::string& aImagePath)
	{
		myImagePath = aImagePath;
	}
	void SpriteSheet::SetPivot(const Tga2D::Vector2f& aPivot)
	{
		mySprite->SetPivot(aPivot);
	}
	void SpriteSheet::SetSize(const Tga2D::Vector2f& aSize)
	{
		mySize = aSize;
	}
	void SpriteSheet::SetSizeRelativeToImage(const Tga2D::Vector2f& aSize)
	{
		mySize.x = mySprite->GetImageSize().x * aSize.x;
		mySize.y = mySprite->GetImageSize().y * aSize.y;

	}
	void SpriteSheet::ResetSize()
	{
		mySize = mySprite->GetImageSize();
	}
	void SpriteSheet::SetFrame(const Tga2D::Vector2f& aCurrentFrame)
	{
		myCurrentFrame = aCurrentFrame;
		mySprite->SetTextureRect(
			myRectSize.x * myCurrentFrame.x - myRectSize.x,	//TopLeftX Current Frame
			myRectSize.y * myCurrentFrame.y - myRectSize.y,	//TopLeftY Current Frame
			myRectSize.x * myCurrentFrame.x,				//BotLeftX Current Frame
			myRectSize.y * myCurrentFrame.y);				//BotLeftY Current Frame
	}
}
