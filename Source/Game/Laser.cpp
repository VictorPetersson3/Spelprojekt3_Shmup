#include "stdafx.h"
#include "Laser.h"

Studio::Laser::Laser(VECTOR2F aPosition) : 
	GameObject("Sprites/Bullets/redlong.dds")
{
	myPosition = aPosition;
	myCollider.AddBoxColliderObject(aPosition, {2000.0f, 25.0f});
	myDamage = 1.0f;
}

Studio::Laser::~Laser()
{
}

void Studio::Laser::Update(float anY)
{
	GameObject::Update({ myPosition.x, anY });
}

float Studio::Laser::GetDamage()
{
	return myDamage;
}
