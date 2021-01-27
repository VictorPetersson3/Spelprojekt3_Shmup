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
		Tga2D::CSprite* GetSprite();
		const std::string& GetImagePath() const;
		const int GetLayer() const;
		
		//Setters
		void SetAmountOfFrames(const Tga2D::Vector2f& aAmountOfFrames);
		void SetPosition(const Tga2D::Vector2f& aPos);
		void SetLayer(signed int aLayer);
		void SetImagePath(const std::string& aImagePath);
		void SetPivot(const Tga2D::Vector2f& aPivot);
		//Pixel Based Size
		void SetSize(const Tga2D::Vector2f& aSize);
		//Image Based Size
		void SetSizeRelativeToImage(const Tga2D::Vector2f& aSize);
		void ResetSize();

		//Animation Function
		void UpdateAnimation();
		void SetFrame(const Tga2D::Vector2f& aCurrentFrame);
		void PlayAnimation(float aSpeed, const std::initializer_list<float> aListOfFrames);
		void PlayAnimationInRange(float aSpeed, const Tga2D::Vector2f& aStartFrame, const Tga2D::Vector2f& aEndFrame);
		void LoopAnimation(float aSpeed, const std::initializer_list<float> aListOfFrames);
		void LoopAnimationInRange(float aSpeed, const Tga2D::Vector2f& aStartFrame, const Tga2D::Vector2f& aEndFrame);
		Tga2D::Vector2f myCurrentFrame;
		

	private:
		signed int myLayer = 0;
		std::string myImagePath;
		Tga2D::CSprite* mySprite = nullptr;
		Tga2D::Vector2<float> myPosition;
		Tga2D::Vector2<float> mySize;
		Tga2D::Vector2f myRectSize;

	};
}
