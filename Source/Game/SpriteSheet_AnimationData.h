#pragma once

namespace Tga2D
{
	class CSprite;
}

namespace Studio
{
	class SpriteSheet_AnimationData
	{
	public:
		SpriteSheet_AnimationData(const std::string& aPath, const unsigned int aAmountOfFrames, const float aAnimationSpeed);
		virtual ~SpriteSheet_AnimationData();

		virtual const unsigned int GetAmountOfFrames() const;
		virtual const float GetRectSize() const;
		virtual const float GetAnimationSpeed() const;
		virtual Tga2D::CSprite* GetSprite();
	private:
		Tga2D::CSprite* mySprite;
		const unsigned int myAmountOfFrames;
		float myRectSize;
		const float myAnimationSpeed;

	};
}


