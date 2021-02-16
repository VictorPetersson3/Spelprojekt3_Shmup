#include "stdafx.h"
#include "AudioManager.h"
#include "AudioClip.h"

Studio::AudioManager::AudioManager()
{
	myAudioEngine = irrklang::createIrrKlangDevice();
}

Studio::AudioManager::~AudioManager()
{
	myAudioEngine->drop();
}

void Studio::AudioManager::Play2D(const char* aPath)
{
	myAudioEngine->play2D(aPath);
}

void Studio::AudioManager::Play2D(const char* aPath, bool aLooping)
{
	myAudioEngine->play2D(aPath, aLooping);
}

void Studio::AudioManager::Play2D(const char* aPath, bool aLooping, float volume)
{
	irrklang::ISoundSource* sound = myAudioEngine->addSoundSourceFromFile(aPath);
	if (sound != nullptr)
	{
		sound->setDefaultVolume(volume*volumeMultiplier);

		myAudioEngine->play2D(sound, aLooping, false, false);

	} 
	else
	{
		myAudioEngine->play2D(myAudioEngine->getSoundSource(aPath), aLooping, false, false);
	}
}

void Studio::AudioManager::Play2D(AudioClip* aClip)
{
	irrklang::ISoundSource* sound = myAudioEngine->addSoundSourceFromFile(aClip->GetSoundFromFile());
	if (sound != nullptr)
	{
		sound->setDefaultVolume(aClip->GetSoundVolume()*volumeMultiplier);

		myAudioEngine->play2D(sound, aClip->IsLooping(), false, true);
	}
	else
	{
		myAudioEngine->play2D(myAudioEngine->getSoundSource(aClip->GetSoundFromFile()), aClip->IsLooping(), false, true);
	}
}

void Studio::AudioManager::StopAllSounds()
{
	myAudioEngine->stopAllSounds();
}

void Studio::AudioManager::StopSound(const char* aPath)
{
	if (myAudioEngine->getSoundSource(aPath) != nullptr)
	{
		myAudioEngine->stopAllSoundsOfSoundSource(myAudioEngine->getSoundSource(aPath));
	}
}

void Studio::AudioManager::StopSound(AudioClip* aClip)
{
	if (myAudioEngine->getSoundSource(aClip->GetSoundFromFile()) != nullptr)
	{
		myAudioEngine->stopAllSoundsOfSoundSource(myAudioEngine->getSoundSource(aClip->GetSoundFromFile()));
	}
}

void Studio::AudioManager::RemoveFileFromEngine(const char* aPath)
{
	if (myAudioEngine->getSoundSource(aPath) != nullptr)
	{
		myAudioEngine->removeSoundSource(myAudioEngine->getSoundSource(aPath));
	}
}

void Studio::AudioManager::RemoveFileFromEngine(AudioClip* aClip)
{
	if (myAudioEngine->getSoundSource(aClip->GetSoundFromFile()) != nullptr)
	{
		myAudioEngine->removeSoundSource(aClip->GetSoundFromFile());
	}
}

void Studio::AudioManager::RemoveAllAudioFromEngine()
{
	myAudioEngine->removeAllSoundSources();
}

void Studio::AudioManager::SetVolumeMultiplier(float aNewMultiplier)
{
	volumeMultiplier = aNewMultiplier;

	myAudioEngine->setSoundVolume(volumeMultiplier);
}

bool Studio::AudioManager::IsCurrentlyPlaying(const char* aPath)
{
	return myAudioEngine->isCurrentlyPlaying(aPath);
}
