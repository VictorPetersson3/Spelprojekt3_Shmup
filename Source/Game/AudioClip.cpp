#include "stdafx.h"
#include "AudioClip.h"

AudioClip::AudioClip(const char* aPath)
{
	myPath = aPath;
	myVolume = 1;
}

AudioClip::AudioClip(const char* aPath, float aVolume)
{
	myPath = aPath;
	myVolume = aVolume;
}

AudioClip::AudioClip(const char* aPath, bool aLooping)
{
	myPath = aPath;
	myVolume = 1;
	myIsLooping = aLooping;
}

AudioClip::AudioClip(const char* aPath, float aVolume, bool aLooping)
{
	myPath = aPath;
	myVolume = aVolume;
	myIsLooping = aLooping;
}

const char* AudioClip::GetSoundFromFile()
{
	return myPath;
}

const float AudioClip::GetSoundVolume()
{
	return myVolume;
}

bool AudioClip::IsLooping()
{
	return myIsLooping;
}


