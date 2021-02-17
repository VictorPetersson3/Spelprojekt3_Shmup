#pragma once
#include "Enums.h"
#include <vector>
#include "tga2d/math/vector2.h"

namespace Studio
{
	class Particle;

	class ParticleEmitter
	{

		public:
			ParticleEmitter();
			~ParticleEmitter();
			void Init(const Enums::EParticleTypes aParticleType);
			void Activate();
			void Deactivate();
			void SpawnParticle();
			void Update();

		private:
			std::vector<Particle*> myParticles;
			int myLatestSpawnedParticle;
			float mySpawnTimer;
			bool myIsActive;
			bool myParticlesAreStillUpdating;
	};
}


