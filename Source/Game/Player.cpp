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
	Player::Player(const char* aImagePath) :
		Player::GameObject(aImagePath, { 1, 8 }, {0.5, 0.5}),
		myEngineFlame("Sprites/assets/player/Flame.dds", { 1, 4 }, { 300 - 48, 540 - 9 })
	{
		myFrames = { 1, 8 };
		myPosition = { 300, 540 };
		mySpeed = 0;
		myShootCooldown = 0.0f;
		myAnimationTime = 0;
		myAnimationTurnSpeed = 0.15;
		myCurrentFlame = 2;
		SAFE_CREATE(myBulletSprite, Tga2D::CSprite("sprites/Bullets/FireBullet.dds"));
		myParticleFactory.InitParticleType("Sprites/Particles/Explosion_01_Temp.dds", 0, "Explosion", 6, 1.5f);
		GetCollider().AddCircleColliderObject(myPosition, 20);
	}

	Player::~Player()
	{
		SAFE_DELETE(myBulletSprite);
	}

	void Player::Update()
	{
		if (!IsDead())
		{
			Movement();

			Player::GameObject::Update(myPosition);
			Player::GameObject::UpdateAnimation(myFrames);

			UpdateBullets();

			Studio::RendererAccessor::GetInstance()->Render(*this);
		}
		
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
	//Temp
	void Player::PlayExplosion()
	{
		if (!myHasDied)
		{
			myParticleObjects.push_back(myParticleFactory.CreateParticleObject("Explosion", myPosition));
			myHasDied = true;
		}
	}

	bool Player::IsFinishedExploding()
	{
		if (myParticleObjects.size() > 0)
		{
			if (myParticleObjects.at(0)->GetHasFinishedAnimation())
			{
				myParticleObjects.erase(myParticleObjects.begin());
				return true;
			}
		}
		
		return false;
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
			if (myIsAnimatingDown)
			{
				myIsAnimatingDown = false;
				myFrames.y = 5;
				myAnimationTime = 0;
			}
			else
			{
				if (!myIsAnimating)
				{
					myFrames.y = 5;
				}
				myIsAnimating = true;
				myIsAnimatingUp = true;
				myAnimationTime += Studio::Timer::GetInstance()->TGetDeltaTime();
				if (myAnimationTime > myAnimationTurnSpeed && myFrames.y != 7)
				{
					myFrames.y++;
					myAnimationTime = 0;
				}
			}
			myPosition.y -= mySpeed * Timer::GetInstance()->TGetDeltaTime();
		}
		//A
		if (aKey && myPosition.x > 0)
		{
			myPosition.x -= mySpeed * Timer::GetInstance()->TGetDeltaTime();
			myCurrentFlame = 1;
		}
		//S
		if (sKey && myPosition.y < 1080)
		{

			if (myIsAnimatingUp)
			{
				myIsAnimatingUp = false;
				myFrames.y = 2;
				myAnimationTime = 0;
			}
			else
			{
				if (!myIsAnimating)
				{
					myFrames.y = 2;
				}
				myIsAnimating = true;
				myIsAnimatingDown = true;
				myAnimationTime += Studio::Timer::GetInstance()->TGetDeltaTime();
				if (myAnimationTime > myAnimationTurnSpeed && myFrames.y != 4)
				{
					myFrames.y++;
					myAnimationTime = 0;
				}
			}
			
			myPosition.y += mySpeed * Timer::GetInstance()->TGetDeltaTime();
		}
		//D
		if (dKey && myPosition.x < 1920)
		{
			myPosition.x += mySpeed * Timer::GetInstance()->TGetDeltaTime();
			myCurrentFlame = 3;
		}
		if (!sKey && !wKey)
		{
			myIsAnimatingUp = false;
			myIsAnimatingDown = false;
			myIsAnimating = false;
			myFrames.y = 1;
		}
		if (!aKey && !dKey)
		{
			myCurrentFlame = 2;
		}
		myEngineFlame.Update(myCurrentFlame, { myPosition.x - 48, myPosition.y - 9 });
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

