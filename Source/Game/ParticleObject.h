#pragma once
#include "GameObject.h"
#include "TypePattern_Particle_SpriteSheet.h"

namespace Studio
{
	class ParticleObject : public GameObject
	{
	public:
		ParticleObject(TypePattern_Particle_SpriteSheet* aTypeObject, const Tga2D::Vector2f& aSpawnPosition);
		~ParticleObject() = default;

		void Update(float aDeltaTime);
		void Render();
		const bool GetHasFinishedAnimation() const;

	private:
		TypePattern_Particle_SpriteSheet* myTypeObject;
		Tga2D::CSprite* mySprite;
		Tga2D::Vector2f myPosition;
		float myLifeTime;
		float myFrameTime;
		float myRectRightSide;
		int myCurrentFrame;
		bool myAnimationHasFinished;
	};
}


