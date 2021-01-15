#pragma once
#include "GameObject.h"

namespace Tga2D
{
	class CSprite;
}

namespace Studio
{
	class BackgroundObject : public GameObject
	{
	public:
		BackgroundObject(Tga2D::CSprite* aSprite, const Tga2D::Vector2f& aPosition, float aSpeed);
		BackgroundObject(Tga2D::CSprite* aSprite, const Tga2D::Vector2f& aPosition, float aSpeed, const Tga2D::Vector2f& aSize);
		~BackgroundObject();
		void Update(float aDeltaTime);
		const Tga2D::Vector2f& GetPosition() const;
		void SetPosition(const Tga2D::Vector2f& aPosition);
	protected:
		Tga2D::Vector2f myPosition;
		float myScrollSpeed;
	private:
		Tga2D::CSprite* mySprite;
	};
}
