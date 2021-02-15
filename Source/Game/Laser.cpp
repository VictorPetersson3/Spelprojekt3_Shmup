#include "stdafx.h"
#include "Laser.h"
#include "RendererAccessor.h"
#include "Renderer.h"
Studio::Laser::Laser(VECTOR2F aPosition) : 
	GameObject("Sprites/Bullets/redlong.dds")
{
	//Figure out a better way to do an offset...
	myPosition = { aPosition.x - 969.0f, aPosition.y - 63.0f };
	myCollider.AddBoxColliderObject({ 0.0f, 0.0f }, { 2000.0f, 25.0f });
	myDamage = 1.0f;
	mySpriteSheet.SetSizeRelativeToImage({25.0f, 1.25f});
}

Studio::Laser::~Laser()
{
}

void Studio::Laser::Update(float anY)
{
	GameObject::Update({ myPosition.x, anY - 63.0f });
	RendererAccessor::GetInstance()->Render(*this);
}

float Studio::Laser::GetDamage()
{
	return myDamage;
}
