#pragma once
#include "SpriteSheet.h"
#include "Enums.h"
namespace Studio
{
	/// <summary>
	/// An abomination of hardcoding, gets stuff done tho
	/// </summary>
	class Cutscenes
	{
	public:
		Cutscenes();
		~Cutscenes();

		void PlayScene(const Enums::Cutscene& aSceneToPlay);
		void UpdateCurrentScene();
		bool IsCurrentyPlaying() const;

	private:
		void UpdateLogoScene(float aDeltaTime);
		void UpdateIntroScene(float aDeltaTime);
		void UpdateOutroScene(float aDeltaTime);
		void LoadResources(const Enums::Cutscene& aSceneToPlay);
		void LoadLogosResources();
		void LoadIntroResources();
		void LoadOutroResources();
		void ReleaseResources(const Enums::Cutscene& aSceneToPlay);
		void ReleaseLogosResources();
		void ReleaseIntroResources();
		void ReleaseOutroResources();

		void GotoNextAction();
		bool RunAboveForXSeconds(float aTime);

		bool myIsCurrentlyPlayingScene = false;
		Enums::Cutscene myCurrentScene;
		float myTime;
		int myActionsDone;

		SpriteSheet* myLogo;

		SpriteSheet* myBackground;
		// Outro Stuff


		// Intro Stuff
	};
}