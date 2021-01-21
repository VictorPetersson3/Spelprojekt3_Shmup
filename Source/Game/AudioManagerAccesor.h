#pragma once
#include "AudioManager.h"

namespace Studio
{
	namespace AudioManagerAccessor
	{	
		AudioManager* GetInstance();
		void Construct();
		void Destruct();
	}
}

