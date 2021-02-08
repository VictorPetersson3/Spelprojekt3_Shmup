#include "stdafx.h"
#include "VideoPlayer.h"
#include "Timer.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/videoplayer/video.h>
namespace Studio
{
	VideoPlayer::VideoPlayer()
	{
		SAFE_CREATE(myVideo, Tga2D::CVideo());
	}
	VideoPlayer::~VideoPlayer()
	{
		SAFE_DELETE(myVideo);
	}
	void VideoPlayer::Update()
	{
		myVideo->Update(DELTA_TIME);
		myIsPlaying = myVideo->GetStatus() == Tga2D::VideoStatus_Playing;
	}
	void VideoPlayer::Render()
	{
		myVideo->Render();
	}
	bool VideoPlayer::IsPlaying() const
	{
		return myIsPlaying;
	}
	void VideoPlayer::PlayVideo(const std::string& aVideoPath)
	{
		myIsPlaying = true;
		LoadVideo(aVideoPath);
		myVideo->Play();
	}
	void VideoPlayer::LoadVideo(const std::string& aVideoPath)
	{
		myVideo->Init(aVideoPath.c_str());
		myVideo->GetSprite()->SetPosition({ 0.0f, 0.0f });
		myVideo->GetSprite()->SetSizeRelativeToScreen({ 16.0f / 9.0f, 1.0f });
	}
}
