#pragma once
#include <map>

namespace Studio
{
	class ParticleObject;
	class TypePattern_Particle_SpriteSheet;
	class Particle_SpriteSheet_Factory
	{
		public:
			Particle_SpriteSheet_Factory() = default;
			~Particle_SpriteSheet_Factory();
			void InitParticleType(const std::string& aPath, const unsigned int aLayerOrder, const std::string& aType, const unsigned int aAmountOfFrames, const float aAnimationSpeed);
			Studio::ParticleObject* CreateParticleObject(const std::string& aType, const Tga2D::Vector2f& aPosition);
		private:
			std::map<std::string, TypePattern_Particle_SpriteSheet*> myParticleObjects;
	};
}



