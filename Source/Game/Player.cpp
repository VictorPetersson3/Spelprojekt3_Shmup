#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "InputManager.h"
#include "tga2d/sprite/sprite.h"
#include "Renderer.h"
#include "RendererAccessor.h"
#include "Timer.h"

namespace Studio
{
	Player::Player(Tga2D::CSprite* aSprite) : 
		Player::GameObject(aSprite)
	{
		myPosition = { 300, 540 };
		mySpeed = 0;
		myShootCooldown = 0.0f;
		mySprite = aSprite;
		mySprite->SetSizeRelativeToImage({ 50, 50 });
		mySprite->SetPivot({ 0.5f, 0.5f });
		SAFE_CREATE(myBulletSprite, Tga2D::CSprite("sprites/debugpixel.dds"));
		myParticleFactory.InitParticleType("Sprites/Particles/Explosion_01_Temp.dds", 0, "Explosion", 6, 3.0f);
		GetCollider().AddCircleColliderObject(myPosition, 20);
	}

	Player::~Player()
	{
		SAFE_DELETE(myBulletSprite);
	}

	void Player::Update()
	{
		Movement();

		Player::GameObject::Update(myPosition);

		UpdateBullets();

		Studio::RendererAccessor::GetInstance()->Render(*this);

		for (int i = 0; i < myBullets.size(); i++)
		{
			Studio::RendererAccessor::GetInstance()->Render(*myBullets[i]);
		}

		if (myParticleObjects.size() > 0)
		{
			myParticleObjects.at(0)->Update(Timer::GetInstance()->TGetDeltaTime());
		}

		//Kod som behöver ligga i levelmanager troligen
		/*for (int i = 0; i < myBullets.size(); i++)
		{
			for (int j = 0; j < myBullets; j++)
			{
				if (myBullets[i]->Intersects(*myEnemies[j]))
				{
					myEnemies.erase(myEnemies.begin() + j);
					break;
				}
			}
		}*/
	}

	void Player::Shoot()
	{
			myShootCooldown += Timer::GetInstance()->TGetDeltaTime();
			if (GetAsyncKeyState(VK_SPACE) && myShootCooldown > 0.1f)
			{
				myBullets.push_back(new Bullet(myPosition, 800, myBulletSprite));
				myShootCooldown = 0;
			}
	}

	void Player::PlayExplosion()
	{
		if (!myHasDied)
		{
			myParticleObjects.push_back(myParticleFactory.CreateParticleObject("Explosion", myPosition));
			myHasDied = true;
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

	void Player::Movement()
	{
		bool wKey = Studio::InputManager::GetInstance()->IsKeyDown('W');
		bool aKey = Studio::InputManager::GetInstance()->IsKeyDown('A');
		bool sKey = Studio::InputManager::GetInstance()->IsKeyDown('S');
		bool dKey = Studio::InputManager::GetInstance()->IsKeyDown('D');
		//W

		if ((wKey && aKey) || (wKey && dKey) || (sKey && aKey) || (sKey && dKey))
		{
			mySpeed = 200;
		}
		else
		{
			mySpeed = 300; //Temp value, change to default value provided by json when added
		}
		
		if (wKey && myPosition.y > 0)
		{
			myPosition.y -= mySpeed * Timer::GetInstance()->TGetDeltaTime();
		}
		//A
		if (aKey && myPosition.x > 0)
		{
			myPosition.x -= mySpeed * Timer::GetInstance()->TGetDeltaTime();
		}
		//S
		if (sKey && myPosition.y < 1080)
		{
			myPosition.y += mySpeed * Timer::GetInstance()->TGetDeltaTime();
		}
		//D
		if (dKey && myPosition.x < 1920)
		{
			myPosition.x += mySpeed * Timer::GetInstance()->TGetDeltaTime();
		}
		
		//Spacebar
		if (Studio::InputManager::GetInstance()->IsKeyDown(VK_SPACE))
		{
			Shoot();
		}
	}

	void Player::UpdateBullets()
	{
		for (int i = 0; i < myBullets.size(); i++)
		{
			myBullets[i]->Update();

			if (myBullets[i]->GetPosition().x > 1920)
			{
				myBullets.erase(myBullets.begin() + i);
			}

		}
	}
}

