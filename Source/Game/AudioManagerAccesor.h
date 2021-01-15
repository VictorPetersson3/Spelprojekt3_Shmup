#pragma once

class AudioManager;

namespace Studio
{
	namespace AudioManagerAccessor
	{	
		AudioManager* GetInstance();
		void SetInstance(AudioManager* aInstance);
	}
}

