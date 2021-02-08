#include "stdafx.h"
#include "Cutscenes.h"
#include "Timer.h"
#include "InputManager.h"
#include "RendererAccessor.h"
#include "Renderer.h"
#include <tga2d/sprite/sprite.h>
namespace Studio
{
	Cutscenes::Cutscenes()
	{
	}
	Cutscenes::~Cutscenes()
	{
	}
	void Cutscenes::LoadLogosResources()
	{
		myLogo = new SpriteSheet("Sprites/Logos/tga_logo.dds");
		myLogo->SetPosition({ 960, 540 });
		myLogo->SetSizeRelativeToImage({ 0.75f, 0.75f });
	}
	void Cutscenes::LoadIntroResources()
	{
	}
	void Cutscenes::LoadOutroResources()
	{
	}
	void Cutscenes::LoadResources(const Enums::Cutscene& aSceneToLoad)
	{
		myTime = 0.0f;
		myActionsDone = 0;
		switch (aSceneToLoad)
		{
		case Studio::Enums::Cutscene::Logos:
			LoadLogosResources();
			break;
		case Studio::Enums::Cutscene::Intro:
			LoadIntroResources();
			break;
		case Studio::Enums::Cutscene::Outro:
			LoadOutroResources();
			break;
		default:
			break;
		}
	}
	void Cutscenes::ReleaseLogosResources()
	{
	}
	void Cutscenes::ReleaseIntroResources()
	{
	}
	void Cutscenes::ReleaseOutroResources()
	{
	}
	void Cutscenes::ReleaseResources(const Enums::Cutscene& aSceneToRelease)
	{
		switch (aSceneToRelease)
		{
		case Studio::Enums::Cutscene::Logos:
			ReleaseLogosResources();
			break;
		case Studio::Enums::Cutscene::Intro:
			ReleaseIntroResources();
			break;
		case Studio::Enums::Cutscene::Outro:
			ReleaseOutroResources();
			break;
		default:
			break;
		}
	}
	void Cutscenes::PlayScene(const Enums::Cutscene& aSceneToPlay)
	{
		myIsCurrentlyPlayingScene = true;
		myCurrentScene = aSceneToPlay;
		LoadResources(aSceneToPlay);
	}
	bool Cutscenes::IsCurrentyPlaying() const
	{
		return myIsCurrentlyPlayingScene;
	}
	void Cutscenes::UpdateCurrentScene()
	{
		auto deltaTime = Timer::GetInstance()->TGetDeltaTime();
		switch (myCurrentScene)
		{
		case Studio::Enums::Cutscene::Logos:
			UpdateLogoScene(deltaTime);
			break;
		case Studio::Enums::Cutscene::Intro:
			UpdateIntroScene(deltaTime);
			break;
		case Studio::Enums::Cutscene::Outro:
			UpdateOutroScene(deltaTime);
			break;
		default:
			myIsCurrentlyPlayingScene = false;
			break;
		}
	}
	void Cutscenes::UpdateLogoScene(float aDeltaTime)
	{
		switch (myActionsDone)
		{
		case 0:
		{
			// Void
			RunAboveForXSeconds(1.5f);
			break;
		}
		case 1:
		{
			// TGA LOGO fade in
			float alpha = myTime / 3.0f;
			myLogo->GetSprite()->SetColor({ 1.0, 1.0, 1.0, alpha });
			RendererAccessor::GetInstance()->Render(*myLogo);

			RunAboveForXSeconds(3.0f);
			break;
		}
		case 2:
		{
			// TOGO LOGO stay
			RendererAccessor::GetInstance()->Render(*myLogo);
			RunAboveForXSeconds(1.0f);
			break;
		}
		case 3:
		{
			// TGA LOGO fade out
			float alpha = myTime / 0.5f;
			myLogo->GetSprite()->SetColor({ 1.0, 1.0, 1.0, 1.0f - alpha });
			RendererAccessor::GetInstance()->Render(*myLogo);

			RunAboveForXSeconds(0.5f);
			break;
		}
		case 4:
		{
			// Resource switch
			myLogo->SetImagePath("Sprites/Logos/flygpirater_logo.dds");
			myLogo->SetSize({ 1024.0f, 1024.0f });
			GotoNextAction();
			break;
		}
		case 5:
		{
			// OUR LOGO fade in
			float alpha = myTime / 3.0f;
			myLogo->GetSprite()->SetColor({ 1.0, 1.0, 1.0, alpha });
			RendererAccessor::GetInstance()->Render(*myLogo);

			RunAboveForXSeconds(3.0f);
			break;
		}
		case 6:
		{
			// OUR LOGO stay
			RendererAccessor::GetInstance()->Render(*myLogo);
			RunAboveForXSeconds(1.0f);
			break;
		}
		case 7:
		{
			// OUR LOGO fade out
			float alpha = myTime / 0.5f;
			myLogo->GetSprite()->SetColor({ 1.0, 1.0, 1.0, 1.0f - alpha });
			RendererAccessor::GetInstance()->Render(*myLogo);

			RunAboveForXSeconds(0.5f);
			break;
		}
		case 8:
		{
			myIsCurrentlyPlayingScene = false;
			break;
		}
		default:
			break;
		}
	}
	void Cutscenes::UpdateIntroScene(float aDeltaTime)
	{
	}
	void Cutscenes::UpdateOutroScene(float aDeltaTime)
	{
	}
	void Cutscenes::GotoNextAction()
	{
		myActionsDone++;
	}
	bool Cutscenes::RunAboveForXSeconds(float aTime)
	{
		myTime += Timer::GetInstance()->TGetDeltaTime();
		if (myTime > aTime)
		{
			myTime -= aTime;
			myActionsDone++;
			return true;
		}
		return false;
	}
}
