#pragma once
namespace Tga2D
{
	class CVideo;
}
namespace Studio
{
	class VideoPlayer
	{
	public:
		VideoPlayer();
		~VideoPlayer();
		void Update();
		void Render();
		void PlayVideo(const std::string& aVideoPath);
		bool IsPlaying() const;
	private:
		void LoadVideo(const std::string& aVideoPath);
		bool myIsPlaying;
		Tga2D::CVideo* myVideo;
	};
}
