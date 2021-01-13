#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "InputManager.h"
#include "tga2d/sprite/sprite.h"

namespace Studio
{
	Player::Player(Tga2D::CSprite* aSprite) : 
		Player::GameObject(aSprite)
	{
		myPosition = { 0.5f, 0.5f };
		mySpeed = 0.3f;
		myShootCooldown = 0.0f;
		mySprite = aSprite;
		mySprite->SetSizeRelativeToImage({ 50, 50 });
		mySprite->SetPivot({ 0.5f, 0.5f });
		SAFE_CREATE(myBulletSprite, Tga2D::CSprite("sprites/debugpixel.dds"));
	}

	Player::~Player()
	{
		SAFE_DELETE(myBulletSprite);
	}

	void Player::Update(float aDeltaTime)
	{
		Movement(aDeltaTime);

		Player::GameObject::Update(myPosition);

		UpdateBullets(aDeltaTime);
	}

	void Player::Shoot(float aDeltaTime)
	{
			myShootCooldown += aDeltaTime;
			if (GetAsyncKeyState(VK_SPACE) && myShootCooldown > 0.1f)
			{
				myBullets.push_back(new Bullet(myPosition, 1.0f, myBulletSprite));
				myShootCooldown = 0;
			}
	}

	std::vector<Bullet*>& Player::GetBullets()
	{
		return myBullets;
	}

	RenderCommand& Player::GetRenderCommand()
	{
		return Player::GameObject::GetRenderCommand();
	}

	void Player::Movement(float aDeltaTime)
	{
		bool wKey = Studio::InputManager::GetInstance()->IsKeyDown('W');
		bool aKey = Studio::InputManager::GetInstance()->IsKeyDown('A');
		bool sKey = Studio::InputManager::GetInstance()->IsKeyDown('S');
		bool dKey = Studio::InputManager::GetInstance()->IsKeyDown('D');
		//W

		if ((wKey && aKey) || (wKey && dKey) || (sKey && aKey) || (sKey && dKey))
		{
			mySpeed = 0.2f;
		}
		else
		{
			mySpeed = 0.3f; //Temp value, change to default value provided by json when added
		}
		
		if (wKey && myPosition.y > 0.05f)
		{
			myPosition.y -= mySpeed * aDeltaTime;
		}
		//A
		if (aKey && myPosition.x > 0.05f)
		{
			myPosition.x -= mySpeed * aDeltaTime;
		}
		//S
		if (sKey && myPosition.y < 0.95f)
		{
			myPosition.y += mySpeed * aDeltaTime;
		}
		//D
		if (dKey && myPosition.x < 0.95f)
		{
			myPosition.x += mySpeed * aDeltaTime;
		}
		
		//Spacebar
		if (Studio::InputManager::GetInstance()->IsKeyDown(VK_SPACE))
		{
			Shoot(aDeltaTime);
		}
	}

	void Player::UpdateBullets(float aDeltaTime)
	{
		for (int i = 0; i < myBullets.size(); i++)
		{
			myBullets[i]->Update(aDeltaTime);

			if (myBullets[i]->GetPosition().x > 1.0f)
			{
				myBullets.erase(myBullets.begin() + i);
			}

		}
	}
}

