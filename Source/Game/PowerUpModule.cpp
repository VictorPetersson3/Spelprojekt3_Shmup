#include "stdafx.h"
#include "PowerUpModule.h"
#include "Renderer.h"
#include "RendererAccessor.h"
#include "PlayerAccessor.h"
#include "tga2d/sprite/sprite.h"
namespace Studio
{
	PowerUpModule::PowerUpModule(Enums::PowerUpModules aPowerUpModule)
	{
		switch (aPowerUpModule)
		{
		case Studio::Enums::PowerUpModules::BasicAttackFirst:
			mySpriteSheet.SetImagePath("Sprites/assets/player/upgrades/basicSprite.dds");
			mySpriteSheet.SetSize({ 128.f,512.f });
			mySpriteSheet.SetAmountOfFrames({ 1,8 });
			break;
		case Studio::Enums::PowerUpModules::BasicAttackSecond:
			mySpriteSheet.SetImagePath("Sprites/assets/player/upgrades/rapidSprite.dds");
			mySpriteSheet.SetSize({ 128.f,512.f });
			mySpriteSheet.SetAmountOfFrames({ 1,8 });
			break;
		case Studio::Enums::PowerUpModules::RapidFire:
			mySpriteSheet.SetImagePath("Sprites/assets/player/upgrades/barrelSprite.dds");
			mySpriteSheet.SetSize({ 128.f,512.f });
			mySpriteSheet.SetAmountOfFrames({ 1,8 });
			break;
		case Studio::Enums::PowerUpModules::Shield:
			myIsShield = true;
			mySpriteSheet.SetImagePath("Sprites/assets/player/upgrades/effects/shieldSpriteBlue_02.dds");
			mySpriteSheet.SetSize({ 512.f,256.f });
			mySpriteSheet.SetAmountOfFrames({ 4,2 });

			break;
		}
		mySpriteSheet.SetLayer(1);
	}
	void PowerUpModule::Update()
	{
		myPosition = PlayerAccessor::GetInstance()->GetPosition();
		GameObject::Update(myPosition);
		RendererAccessor::GetInstance()->Render(*this);
	}
	bool PowerUpModule::GetIsShield()
	{
		return myIsShield;
	}
}