#pragma once

class AudioClip
{
public:
	AudioClip(const char* aPath);
	AudioClip(const char* aPath, float aVolume);
	AudioClip(const char* aPath, bool aLooping);
	AudioClip(const char* aPath, float aVolume, bool aLooping);

	const char* GetSoundFromFile();
	const float GetSoundVolume();
	bool IsLooping();

private:
	const char* myPath;
	float myVolume;
	bool myIsLooping = false;
};

