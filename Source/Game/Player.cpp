#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "InputManager.h"
#include "tga2d/sprite/sprite.h"
#include "Renderer.h"
#include "RendererAccessor.h"
#include "CoinAccessor.h"
#include "ScoreAccessor.h"
#include "Coin.h"
#include "Timer.h"

#define SPRITESHEET GameObject::GetSpriteSheet()

namespace Studio
{
	Player::Player(const char* aImagePath) :
		Player::GameObject(aImagePath),
		myEngineFlame("sprites/assets/player/Flame.dds", { 1, 4 }, { 300 - 48, 540 - 9 })
	{
		SPRITESHEET.SetAmountOfFrames({ 1, 8 });
		myEngineFlame.GetSpriteSheet().SetLayer(-1);
		myFrames = { 1, 8 };
		myPosition = { 300, 540 };
		mySpeed = 0;
		myShootCooldown = 0.0f;
		myAnimationTime = 0;
		myAnimationTurnSpeed = 0.075;
		myCurrentFlame = 2;
		SAFE_CREATE(myBulletSprite, Tga2D::CSprite("sprites/Bullets/FireBullet.dds"));
		myParticleFactory.InitParticleType("sprites/Particles/Explosion_01_Temp.dds", 0, "Explosion", 6, 1.5f);
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

		auto& worldCoins = CoinAccessor::GetInstance()->GetWorldCoins();

		for (int i = 0; i < worldCoins.size(); i++)
		{
			if (worldCoins[i]->Intersects(*this))
			{
				ScoreAccessor::GetInstance()->AddCoinScore(1);
				worldCoins.erase(worldCoins.begin() + i);

				printf_s("bruh");
			}
		}
		

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
			if (myIsAnimatingDown || !myIsAnimating)
			{
				myIsAnimatingDown = false;
				GameObject::GetSpriteSheet().PlayAnimationInRange(myAnimationTurnSpeed, { 1, 5 }, { 1, 7 });
				myIsAnimatingUp = true;
				myIsAnimating = true;
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
			if (myIsAnimatingUp || !myIsAnimating)
			{
				myIsAnimatingUp = false;
				GameObject::GetSpriteSheet().PlayAnimationInRange(myAnimationTurnSpeed, { 1, 2 }, { 1, 4 });
				myIsAnimatingDown = true;
				myIsAnimating = true;
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

			if (myIsAnimating)
			{
				if (myIsAnimatingDown)
				{
					if (!myIsRebounding)
					{
						SPRITESHEET.ReverseAndStartAnimation();
						myIsRebounding = true;
					}
					else
					{
						if (!SPRITESHEET.IsAnimating())
						{
							myIsAnimating = false;
						}
					}
				}
				if (myIsAnimatingUp)
				{
					if (!myIsRebounding)
					{
						SPRITESHEET.ReverseAndStartAnimation();
						myIsRebounding = true;
					}
					else
					{
						if (!SPRITESHEET.IsAnimating())
						{
							myIsAnimating = false;
						}
					}
				}
			}
			else
			{
				myIsAnimatingUp = false;
				myIsAnimatingDown = false;
				myIsAnimating = false;
				myIsRebounding = false;
				Player::GameObject::SetFrame({ 1, 1 });
			}
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

