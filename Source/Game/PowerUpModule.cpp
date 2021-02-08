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
			mySpriteSheet.SetAmountOfFrames({ 1,8 });
			break;
		case Studio::Enums::PowerUpModules::BasicAttackSecond:
			mySpriteSheet.SetImagePath("Sprites/assets/player/upgrades/rapidSprite.dds");
			mySpriteSheet.SetAmountOfFrames({ 1,8 });
			break;
		case Studio::Enums::PowerUpModules::RapidFire:
			mySpriteSheet.SetImagePath("Sprites/assets/player/upgrades/barrelSprite.dds");
			mySpriteSheet.SetAmountOfFrames({ 1,8 });
			break;
		case Studio::Enums::PowerUpModules::Shield:
			myIsShield = true;
			mySpriteSheet.SetImagePath("Sprites/assets/player/upgrades/effects/shieldSpriteRed.dds");
			mySpriteSheet.SetAmountOfFrames({ 4,4 });

			break;
		}
		mySpriteSheet.SetLayer(3);
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