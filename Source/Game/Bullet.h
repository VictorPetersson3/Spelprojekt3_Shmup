#pragma once
#include "GameObject.h"
namespace Tga2D
{
	class CSprite;
}
namespace Studio
{
	class RenderCommand;
	class Bullet : public GameObject
	{
	public:
		Bullet() = default;
		Bullet(VECTOR2F aPosition, const float& aSpeed, Tga2D::CSprite* aSprite);
		~Bullet();
		void Update(float aDeltaTime);

		VECTOR2F GetPosition();

		Studio::RenderCommand GetRenderCommand();

	private:
		float mySpeed;

		Tga2D::CSprite* mySprite;

		VECTOR2F myPosition;
	};
}


