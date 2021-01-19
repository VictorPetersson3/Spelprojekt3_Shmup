#include "stdafx.h"
#include "Bullet.h"
#include "tga2d/sprite/sprite.h"
namespace Studio
{
	Bullet::Bullet(VECTOR2F aPosition, const float& aSpeed, Tga2D::CSprite* aSprite) : 
		Bullet::GameObject(aSprite)
	{
		myPosition = aPosition;
		mySpeed = aSpeed;

		Bullet::GameObject::GetCollider().AddCircleColliderObject(myPosition, 0.005f);

		SAFE_CREATE(mySprite, Tga2D::CSprite(*aSprite));

		aSprite->SetSizeRelativeToScreen({ 0.01f, 0.01f });
		aSprite->SetPivot({ 0.5f, 0.5f });
	}

	Bullet::~Bullet()
	{
		SAFE_DELETE(mySprite);
	}

	void Bullet::Update(float aDeltaTime)
	{
		myPosition.x += mySpeed * aDeltaTime;

		Bullet::GameObject::Update(myPosition);
	}

	VECTOR2F Bullet::GetPosition()
	{
		return myPosition;
	}
	Studio::RenderCommand Bullet::GetRenderCommand()
	{
		return Bullet::GameObject::GetRenderCommand();
	}
}

