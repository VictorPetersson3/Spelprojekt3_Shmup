#include "stdafx.h"
#include "AudioManagerAccesor.h"

class AudioManager;

namespace Studio
{
	namespace AudioManagerAccessor
	{
		namespace
		{
			AudioManager* myAudioManager;
		}

		AudioManager* GetInstance()
		{
			return myAudioManager;
		}

		void SetInstance(AudioManager* aInstance)
		{
			myAudioManager = aInstance;
		}
	}
}