#pragma once
namespace Tga2D
{
	class CSprite;
	class CColor;
}
namespace Studio
{
	class SpriteSheet
	{
	public:

		SpriteSheet(const char* aImagePath);
		/// <summary>
		/// Constructor for Animation
		/// </summary>
		/// <param name="aImagePath"></param>
		/// <param name="aAmountOfFrames"></param>
		/// <param name="aPivot"></param>
		SpriteSheet(const char* aImagePath, const Tga2D::Vector2f& aAmountOfFrames);
		~SpriteSheet();

		// Copy constructor
		SpriteSheet(const SpriteSheet& aCopy);

		// Move constructor
		SpriteSheet(SpriteSheet&&);

		// Assignment operator
		//SpriteSheet& operator=(const SpriteSheet& aReference);

		// Move Assignment operator
		SpriteSheet& operator=(SpriteSheet&&) = delete;

		//Getters
		Tga2D::Vector2<float>& GetSize();
		Tga2D::Vector2<float>& GetPosition();
		Tga2D::Vector2<float>& GetCurrentFrame();
		Tga2D::CSprite* GetSprite();
		const std::string& GetImagePath() const;
		const int GetLayer() const;
		const bool IsAnimating() const;
		//Setters
		void SetAmountOfFrames(const Tga2D::Vector2f& aAmountOfFrames);
		void SetPosition(const Tga2D::Vector2f& aPos);
		void SetLayer(signed int aLayer);
		void SetImagePath(const std::string& aImagePath);
		void SetPivot(const Tga2D::Vector2f& aPivot);
		void SetColor(const Tga2D::CColor& aColor);
		//Pixel Based Size
		void SetSize(const Tga2D::Vector2f& aSize);
		//Image Based Size
		void SetSizeRelativeToImage(const Tga2D::Vector2f& aSize);
		void ResetSize();

		//Animation Functions
		void UpdateAnimation();
		void SetFrame(const Tga2D::Vector2f& aCurrentFrame);

		void ReverseAndStartAnimation();
		const float GetRotation() const;
		void SetRotation(const float aRotationInRadians);


		void PlayAnimation(float aSpeed, const std::initializer_list<float> aListOfFrames);
		void PlayAnimationInRange(float aSpeed, const Tga2D::Vector2f& aStartFrame, const Tga2D::Vector2f& aEndFrame);
		void LoopAnimation(float aSpeed, const std::initializer_list<float> aListOfFrames);
		void LoopAnimationInRange(float aSpeed, const Tga2D::Vector2f& aStartFrame, const Tga2D::Vector2f& aEndFrame);


		void StopAnimation();
		void ResumeAnimation();
		

	private:
		void SetFrame();
		void PlayForward();
		void PlayBackward();

		bool myIsAnimating;
		bool myIsLooping;
		bool myIsPlayingBackwards;
		bool myAnimationIsDone;
		float myAnimationTime;
		float myAnimationSpeed;
		std::vector<std::pair<float, float>> myListOfFramesToPlay;
		Tga2D::Vector2f myCurrentFrame;
		Tga2D::Vector2<float> myAmountOfFrames;
		Tga2D::Vector2<float> myStartFrame;
		Tga2D::Vector2<float> myEndFrame;
		int myFrameInAnimation;
		signed int myLayer = 0;
		std::string myImagePath;
		Tga2D::CSprite* mySprite = nullptr;
		Tga2D::Vector2<float> myPosition;
		Tga2D::Vector2<float> mySize;
		Tga2D::Vector2f myRectSize;

	};
}
