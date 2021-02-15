#include "stdafx.h"
#include "VideoPlayer.h"
#include "Timer.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/videoplayer/video.h>
namespace Studio
{
	VideoPlayer::VideoPlayer()
	{
		myVideo = nullptr;
		myIsPlaying = false;
	}
	VideoPlayer::~VideoPlayer()
	{
		SAFE_DELETE(myVideo);
	}
	void VideoPlayer::Update()
	{
		myIsPlaying = myVideo->GetStatus() == Tga2D::VideoStatus_Playing;
		if (myIsPlaying)
		{
			myVideo->Update(DELTA_TIME);
		}
		else
		{
			UnloadVideo();
		}
	}
	void VideoPlayer::Render()
	{
		myVideo->Render();
	}
	bool VideoPlayer::IsPlaying() const
	{
		return myIsPlaying;
	}
	void VideoPlayer::PlayVideo(const Enums::Video& aVideoToPlay)
	{
		switch (aVideoToPlay)
		{
		case Enums::Video::Logos:
		{
			// TODO: Change to correct .mp4
			PlayVideo("Vidoes/Logos.mp4");
			break;
		}
		case Enums::Video::Intro:
		{
			// TODO: Change to correct .mp4
			PlayVideo("Vidoes/Intro.mp4");
			break;
		}
		case Enums::Video::Outro:
		{
			// TODO: Change to correct .mp4
			PlayVideo("Vidoes/Outro.mp4");
			break;
		}
		default:
			break;
		}
	}
	void VideoPlayer::PlayVideo(const std::string& aVideoPath)
	{
		printf_s("Video: Tries to play \"%s\"\n", aVideoPath.c_str());

		myIsPlaying = true;
		LoadVideo(aVideoPath);
		myVideo->Play();

		printf_s("Video: %s\n", IsPlaying() ? "Succeeded" : "Failed");
	}
	void VideoPlayer::LoadVideo(const std::string& aVideoPath)
	{
		UnloadVideo();
		SAFE_CREATE(myVideo, Tga2D::CVideo());
		myVideo->Init(aVideoPath.c_str());
		myVideo->GetSprite()->SetPosition({ 0.0f, 0.0f });
		myVideo->GetSprite()->SetSizeRelativeToScreen({ 16.0f / 9.0f, 1.0f });
	}
	void VideoPlayer::UnloadVideo()
	{
		if (myVideo != nullptr)
		{
			SAFE_DELETE(myVideo);
		}
	}
}
