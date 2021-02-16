#pragma once
#include "tga2d/math/color.h"
#include "Enums.h"

namespace Studio
{
	class SpriteSheet;
	class Particle
	{
	public:
		Particle(const Enums::EParticleTypes aParticleType);
		~Particle();
		void Init();
		const bool IsActive() const;
		void SpawnParticle();
		void Update();
		void UpdateColor();
		void Render();

	private:
		bool myIsActive;
		bool myIsRotatingFollowDirection;
		bool myUse3Colors;
		bool myIsRotatingRandomDir;

		float myStartRotation;
		float myRotationDirection;
		float myRotationSpeed;
		float myGravity;
		float myVelocity;
		float myLifeTime;
		float myCurrentTime;
		float myWindStrength;
		float myRotation;
		Tga2D::CColor myStartColor;
		Tga2D::CColor myMidColor;
		Tga2D::CColor myEndColor;

		Tga2D::Vector2f myDirection;
		Tga2D::Vector2f myPosition;
		Tga2D::Vector2f myAroundCenterPos;
		Tga2D::Vector2f myWindDirection;
		Tga2D::Vector2f myStartSize;
		Tga2D::Vector2f myEndSize;
		Enums::EParticleTypes myParticleType;
		SpriteSheet* mySprite;
	};

}

