#include "stdafx.h"
#include "SpriteSheet.h"
#include <tga2d/sprite/sprite.h>
#include <string>
#include "Timer.h"


namespace Studio
{
	SpriteSheet::SpriteSheet(const char* aImagePath)
	{
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
		myIsAnimating = false;
		myIsLooping = false;
		myAnimationIsDone = true;
		myAnimationSpeed = 0;
		myAnimationTime = 0;
	}

	SpriteSheet::SpriteSheet(const char* aImagePath, const Tga2D::Vector2f& aAmountOfFrames) :
		SpriteSheet(aImagePath)
	{
		SetAmountOfFrames(aAmountOfFrames);
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
	Tga2D::Vector2<float>& SpriteSheet::GetCurrentFrame()
	{
		return myCurrentFrame;
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
	const bool SpriteSheet::IsAnimating() const
	{
		return myIsAnimating;
	}
	void SpriteSheet::SetAmountOfFrames(const Tga2D::Vector2f& aAmountOfFrames)
	{
		myRectSize.x = (mySize.x / aAmountOfFrames.x) / mySize.x;
		myRectSize.y = (mySize.y / aAmountOfFrames.y) / mySize.y;
		mySprite->SetTextureRect(myRectSize.x - myRectSize.x, myRectSize.y - myRectSize.y, myRectSize.x, myRectSize.y);
		mySize.x = mySize.x / aAmountOfFrames.x;
		mySize.y = mySize.y / aAmountOfFrames.y;
		myAmountOfFrames = aAmountOfFrames;
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
	void SpriteSheet::SetColor(const Tga2D::CColor& aColor)
	{
		mySprite->SetColor(aColor);
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




	void SpriteSheet::UpdateAnimation()
	{
		if (myIsAnimating)
		{
			if (!myIsPlayingBackwards)
			{
				PlayForward();
			}
			else
			{
				PlayBackward();
			}
		}
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

	void SpriteSheet::ReverseAndStartAnimation()
	{
		myIsPlayingBackwards = true;
		myIsAnimating = true;
	}

	const float SpriteSheet::GetRotation() const
	{
		return mySprite->GetRotation();
	}

	void SpriteSheet::SetRotation(const float aRotationInRadians)
	{
		mySprite->SetRotation(aRotationInRadians);
	}

	void SpriteSheet::PlayAnimation(float aSpeed, const std::initializer_list<float> aListOfFrames)
	{
		myFrameInAnimation = 1;
		myListOfFramesToPlay.clear();
		myAnimationSpeed = aSpeed;
		for (int i = 0; i < aListOfFrames.size(); i + 2)
		{
			myListOfFramesToPlay.push_back(std::pair<float, float>(*aListOfFrames.begin() + i, *aListOfFrames.begin() + i + 1));
		}
		myIsAnimating = true;
		myIsLooping = false;
		myAnimationIsDone = false;
		myIsPlayingBackwards = false;
	}

	void SpriteSheet::PlayAnimationInRange(float aSpeed, const Tga2D::Vector2f& aStartFrame, const Tga2D::Vector2f& aEndFrame)
	{
		myFrameInAnimation = 1;
		myListOfFramesToPlay.clear();
		myAnimationSpeed = aSpeed;
		myStartFrame = aStartFrame;
		myCurrentFrame = aStartFrame;
		myEndFrame = aEndFrame;
		myIsAnimating = true;
		myIsLooping = false;
		myAnimationIsDone = false;
		myIsPlayingBackwards = false;
	}

	void SpriteSheet::LoopAnimation(float aSpeed, const std::initializer_list<float> aListOfFrames)
	{
		PlayAnimation(aSpeed, aListOfFrames);
		myIsLooping = true;
		myIsPlayingBackwards = false;
	}

	void SpriteSheet::LoopAnimationInRange(float aSpeed, const Tga2D::Vector2f& aStartFrame, const Tga2D::Vector2f& aEndFrame)
	{
		PlayAnimationInRange(aSpeed, aStartFrame, aEndFrame);
		myIsLooping = true;
		myIsPlayingBackwards = false;
	}


	void SpriteSheet::StopAnimation()
	{
		myIsAnimating = false;
	}

	void SpriteSheet::ResumeAnimation()
	{
		if (!myIsAnimating && !myAnimationIsDone)
		{
			myIsAnimating = true;
		}
	}

	void SpriteSheet::SetFrame()
	{
		mySprite->SetTextureRect(
			myRectSize.x * myCurrentFrame.x - myRectSize.x,	//TopLeftX Current Frame
			myRectSize.y * myCurrentFrame.y - myRectSize.y,	//TopLeftY Current Frame
			myRectSize.x * myCurrentFrame.x,				//BotLeftX Current Frame
			myRectSize.y * myCurrentFrame.y);				//BotLeftY Current Frame
	}

	void SpriteSheet::PlayForward()
	{
		myAnimationTime += Studio::Timer::GetInstance()->TGetDeltaTime();
		if (myListOfFramesToPlay.empty())
		{
			if (myAnimationTime > myAnimationSpeed)
			{
				if (myCurrentFrame.x >= myEndFrame.x && myCurrentFrame.y >= myEndFrame.y)
				{
					if (myIsLooping)
					{
						myCurrentFrame = myStartFrame;
					}
					else
					{
						myIsAnimating = false; 
						myAnimationIsDone = true;
					}
				}
				else
				{
					if (myCurrentFrame.x >= myAmountOfFrames.x)
					{
						myCurrentFrame.y++;
						myCurrentFrame.x = 1;
					}
					else
					{
						myCurrentFrame.x++;
					}
				}
				myAnimationTime = 0;
			}
		}
		else
		{
			if (myAnimationTime > myAnimationSpeed)
			{
				myFrameInAnimation++;
				if (myFrameInAnimation < myListOfFramesToPlay.size())
				{
					myCurrentFrame.x = myListOfFramesToPlay.at(myFrameInAnimation).first;
					myCurrentFrame.y = myListOfFramesToPlay.at(myFrameInAnimation).second;
				}
				else
				{
					if (!myIsLooping)
					{
						myIsAnimating = false;
						myAnimationIsDone = true;
					}
					myFrameInAnimation = 0;
				}
				myAnimationTime = 0;
			}
		}
		SetFrame();
	}

	void SpriteSheet::PlayBackward()
	{
		myAnimationTime += Studio::Timer::GetInstance()->TGetDeltaTime();
		if (myListOfFramesToPlay.empty())
		{
			if (myAnimationTime > myAnimationSpeed)
			{
				if (myCurrentFrame.x <= myStartFrame.x && myCurrentFrame.y <= myStartFrame.y)
				{
					if (myIsLooping)
					{
						myCurrentFrame = myStartFrame;
					}
					else
					{
						myIsAnimating = false;
						myAnimationIsDone = true;
					}
				}
				else
				{
					if (myCurrentFrame.x <= 1)
					{
						myCurrentFrame.y--;
						myCurrentFrame.x = myAmountOfFrames.x;
					}
					else
					{
						myCurrentFrame.x--;
					}
				}
				myAnimationTime = 0;
			}
		}
		else
		{
			if (myAnimationTime > myAnimationSpeed)
			{
				myFrameInAnimation--;
				if (myFrameInAnimation >= 0)
				{
					myCurrentFrame.x = myListOfFramesToPlay.at(myFrameInAnimation).first;
					myCurrentFrame.y = myListOfFramesToPlay.at(myFrameInAnimation).second;
				}
				else
				{
					if (!myIsLooping)
					{
						myIsAnimating = false;
						myAnimationIsDone = true;
					}
					myFrameInAnimation = myListOfFramesToPlay.size() - 1;
				}
				myAnimationTime = 0;
			}
		}
		SetFrame();
	}






}
