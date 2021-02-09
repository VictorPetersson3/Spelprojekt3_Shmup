#pragma once
#include "VideoPlayer.h"
namespace Studio
{
    namespace VideoPlayerAccessor
    {
        VideoPlayer* GetInstance();
        void SetInstance(VideoPlayer*);
    }
}