#pragma once
#include "irrKlang\irrKlang.h"

class AudioClip;

namespace Studio
{
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		irrklang::ISoundEngine* myAudioEngine;

		void Play2D(const char* aPath);
		void Play2D(const char* aPath, bool aLooping);
		void Play2D(const char* aPath, bool aLooping, float volume);


		void Play2D(AudioClip* aClip);

		void StopAllSounds();
		void StopSound(const char* aPath);
		void StopSound(AudioClip* aClip);

		void RemoveFileFromEngine(const char* aPath);
		void RemoveFileFromEngine(AudioClip* aClip);
		void RemoveAllAudioFromEngine();

		void SetVolumeMultiplier(float aNewMultiplier);

		bool IsCurrentlyPlaying(const char* aPath);

	private:
		float volumeMultiplier = 1;
	};
}

