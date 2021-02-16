#include "stdafx.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include "Timer.h"
Studio::ParticleEmitter::ParticleEmitter()
{
	myLatestSpawnedParticle = 0;
	mySpawnTimer = 0;
	myIsActive = false;
	myParticlesAreStillUpdating = false;
}

Studio::ParticleEmitter::~ParticleEmitter()
{
	for (int i = 0; i < myParticles.size(); i++)
	{
		delete myParticles[i];
		myParticles[i] = nullptr;
	}
	myParticles.clear();
}

void Studio::ParticleEmitter::Init(const Enums::EParticleTypes aParticleType)
{
	for (int i = 0; i < 100; i++)
	{
		myParticles.push_back(new Particle(aParticleType));
	}
}

void Studio::ParticleEmitter::Activate()
{
	myIsActive = true;
}

void Studio::ParticleEmitter::Deactivate()
{
	myIsActive = false;
}

void Studio::ParticleEmitter::SpawnParticle()
{
	
	if (myIsActive)
	{
		mySpawnTimer += Studio::Timer::GetInstance()->TGetDeltaTime();
		if (mySpawnTimer > 0.025f)
		{
			for (int i = myLatestSpawnedParticle; i < myParticles.size(); i++)
			{
				if (!myParticles[i]->IsActive())
				{
					myParticles[i]->SpawnParticle();
					myLatestSpawnedParticle++;
					if (myLatestSpawnedParticle >= myParticles.size())
					{
						myLatestSpawnedParticle = 0;
					}
					mySpawnTimer = 0;
					break;
				}
			}
		}
	}
}

void Studio::ParticleEmitter::Update()
{

	if (myIsActive)
	{
		myParticlesAreStillUpdating = false;
		for (Particle* particle : myParticles)
		{
			if (particle->IsActive())
			{
				particle->Update();
				if (particle->IsActive())
				{
					myParticlesAreStillUpdating = true;
				}
			}

		}
	}
}
