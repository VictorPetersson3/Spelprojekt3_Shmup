#include "stdafx.h"
#include "VideoPlayerAccessor.h"
namespace Studio
{
    namespace VideoPlayerAccessor
    {
        namespace
        {
            VideoPlayer* myInstance;
        }

        VideoPlayer* GetInstance()
        {
            return myInstance;
        }

        void SetInstance(VideoPlayer* aVideoPlayer)
        {
            myInstance = aVideoPlayer;
        }
    }
}