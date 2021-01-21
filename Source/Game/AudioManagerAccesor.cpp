#include "stdafx.h"
#include "AudioManagerAccesor.h"
#include "AudioManager.h"

namespace Studio
{
	namespace AudioManagerAccessor
	{
		namespace
		{
			AudioManager* myAudioManager;
		}

		void Construct()
		{
			myAudioManager = new AudioManager();
		}

		void Destruct()
		{
			delete myAudioManager;
			myAudioManager = nullptr;
		}

		AudioManager* GetInstance()
		{
			return myAudioManager;
		}
	}
}