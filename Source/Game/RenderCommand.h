#pragma once
#include "../tga2dcore/tga2d/math/vector2imp.h"

namespace Tga2D
{
	class CSprite;
}
namespace Studio
{
	class RenderCommand
	{
		public:
			RenderCommand();
			RenderCommand(Tga2D::CSprite* aSprite);
			RenderCommand(Tga2D::CSprite* aSprite, const Tga2D::Vector2f& aSize);
			~RenderCommand();

			virtual void Update(const Tga2D::Vector2f& aPos);
			virtual void Update(const Tga2D::Vector2f& aPos, Tga2D::CSprite* aSprite);
			virtual void Update(Tga2D::CSprite* aSprite, const float aRotation);
			virtual void Update(const Tga2D::Vector2f& aPos, const float aRotation, Tga2D::CSprite* aSprite);
			void Render();
			virtual void SetScale(const Tga2D::Vector2f& aScale);
			Tga2D::CSprite* GetSprite() const;

	private:
		float myRotation;
		Tga2D::CSprite* mySprite;
		Tga2D::Vector2f myPosition;
		Tga2D::Vector2f myScale;
	};


}


