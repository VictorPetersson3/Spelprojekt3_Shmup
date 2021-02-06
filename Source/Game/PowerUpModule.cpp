#include "stdafx.h"
#include "PowerUpModule.h"
#include "Renderer.h"
#include "RendererAccessor.h"
#include "PlayerAccessor.h"
namespace Studio
{
	PowerUpModule::PowerUpModule(Enums::PowerUpModules aPowerUpModule)
	{
		switch (aPowerUpModule)
		{
		case Studio::Enums::PowerUpModules::BasicAttack:
			mySpriteSheet.SetImagePath("Sprites/assets/player/upgrades/basicSprite.dds");
			break;
		case Studio::Enums::PowerUpModules::RapidFire:
			mySpriteSheet.SetImagePath("Sprites/assets/player/upgrades/barrelSprite.dds");
			break;
		case Studio::Enums::PowerUpModules::Shield:
			mySpriteSheet.SetImagePath("Sprites/assets/player/upgrades/effets/shieldEffect.dds");
			break;
		}
		mySpriteSheet.SetAmountOfFrames({ 1,8 });
		mySpriteSheet.SetLayer(3);
	}
	void PowerUpModule::Update()
	{
		myPosition = PlayerAccessor::GetInstance()->GetPosition();
		GameObject::Update(myPosition);
		RendererAccessor::GetInstance()->Render(*this);
	}
}