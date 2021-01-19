#include "stdafx.h"
#include "Particle_SpriteSheet_Factory.h"
#include "ParticleObject.h"
#include "TypePattern_Particle_SpriteSheet.h"

Studio::Particle_SpriteSheet_Factory::~Particle_SpriteSheet_Factory()
{
	for (auto it = myParticleObjects.begin(); it != myParticleObjects.end(); ++it)
	{
		delete (*it).second;
		SAFE_DELETE((*it).second);
	}
}

void Studio::Particle_SpriteSheet_Factory::InitParticleType(const std::string& aSpritePath, const unsigned int aLayerOrder, const std::string& aType, const unsigned int aAmountOfFrames, const float aAnimationSpeed)
{
	std::pair<std::string, Studio::TypePattern_Particle_SpriteSheet*> temp_pair(aType, new Studio::TypePattern_Particle_SpriteSheet(aSpritePath, aLayerOrder, aAmountOfFrames, aAnimationSpeed));
	myParticleObjects.insert(temp_pair);
}

Studio::ParticleObject* Studio::Particle_SpriteSheet_Factory::CreateParticleObject(const std::string& aType, const Tga2D::Vector2f& aPosition)
{
	Studio::ParticleObject* tempObject = new Studio::ParticleObject(myParticleObjects.at(aType), aPosition);
	return tempObject;
}