#include "stdafx.h"
#include "LevelManager.h"
#include "rapidjson/document.h"

// Filhantering
#include <fstream>
#include <sstream>
#include <filesystem>

// Spelfiler
#include "Timer.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Missile.h"
#include "AOEBullet.h"
#include "TimedBomb.h"
#include "Pack.h"
#include "EnemyFactory.h"
#include "BulletFactory.h"
#include "Player.h"
#include "Boss.h"
#include "BossManager.h"
#include "BackgroundManager.h"
#include "EffectExplosionLarge.h"
#include "CoinAccessor.h"
#include "Laser.h"
#include "ParticleEmitter.h"

// Rendering
#include "RendererAccessor.h"
#include "Renderer.h"
#include <tga2d/sprite/sprite.h>

// Menu
#include "MenuManagerSingleton.h"
#include "MenuManager.h"
#include "MenuObject.h"

// Input
#include "InputManager.h"

//Audio
#include "AudioManager.h"
#include "AudioManagerAccesor.h"

// Cutscenes
#include "VideoPlayerAccessor.h"

namespace Studio
{
	LevelManager::LevelManager(BackgroundManager* aBackgroundManager, Player* aPlayer) :
		myBackgroundManager(aBackgroundManager),
		myPlayer(aPlayer)

	{
		SAFE_CREATE(myEnemyFactory, EnemyFactory());
		SAFE_CREATE(myBulletFactory, BulletFactory());
		myBoss = nullptr;
		myEnemyFactory->InitAllEnemyTypes();

		SAFE_CREATE(myBossManager, BossManager());

		//temp BulletFactory to try and spawn bullets via LevelManager -->Pu
		myBulletFactory->InitBulletType("Sprites/Bullets/redround.dds", 12, "Enemy", -500.0f, Enums::BulletOwner::Enemy);
		myBulletFactory->InitBulletType("Sprites/Bullets/FireBullet.dds", 12, "Player", 800.0f, Enums::BulletOwner::Player);
		myBulletFactory->InitBulletType("Sprites/Bullets/redround.dds", 12, "Boss", -900.0f, Enums::BulletOwner::Enemy);
		myBossManager->LoadBosses();
		// Load chosen level by Lever Designers
		std::fstream file;
		std::string levelPath;
		int levelIterator = 0;
		int levelToStart = 0;
		file.open("JSON/Levels/level.txt");
		{
			bool lineIsComment = true;
			// Loop through file until line is not a comment
			do
			{
				std::getline(file, levelPath);
				lineIsComment = (levelPath[0] == '#');
			} while (lineIsComment);
		}
		file.close();
		std::string path = "JSON/Levels/";
		path.append(levelPath);
		path.append(".json");

		//printf_s("PATH %s\n", path.c_str());

		std::string directory = "JSON/Levels";
		for (const auto& entry : std::filesystem::directory_iterator(directory))
		{
			if (entry.path().extension().string() == ".json")
			{

				auto file = entry.path().string();

				std::string type = file.substr(12);
				std::string levelPathStitched = "JSON/Levels/";
				levelPathStitched.append(type);
				myLevelPaths.push_back(levelPathStitched);
				printf("LevelPath: %s\n", levelPathStitched.c_str());

				if (path == levelPathStitched)
				{
					levelToStart = levelIterator;
				}
				levelIterator++;
			}
		}
		myCurrentLevel = levelToStart;
		myParticleEmitter = nullptr;
		myLevelBossSpawned = false;
		myLevelEnemiesCleared = false;
		myLevelIsCleared = false;
		myHasReloaded = false;
	}

	LevelManager::~LevelManager()
	{
		SAFE_DELETE(myEnemyFactory);
		SAFE_DELETE_VECTOR(myPacks);
		SAFE_DELETE_VECTOR(myEnemies);
		SAFE_DELETE_VECTOR(myBullets);
		SAFE_DELETE_VECTOR(myExplosions);
		SAFE_DELETE(myBulletFactory);
		SAFE_DELETE(myBossManager);
		if (myLaser != nullptr)
		{
			SAFE_DELETE(myLaser);
		}
	}

	void LevelManager::Update()
	{
		if (!myIsUpdating) return;

		if (Studio::InputManager::GetInstance()->IsKeyPressed('H'))
		{
			ScoreAccessor::GetInstance()->AddCoinScore(100000);
		}


		if (myLevelIsCleared == true)
		{
			if (myCurrentLevel > myLevelPaths.size() - 1)
			{
				//StartCredits
				StopUpdating();
				//Studio::MenuManagerSingleton::GetInstance()->GetMainMenu()->Enable();
				MenuManagerSingleton::GetInstance()->GetHUD()->Disable();
				MenuManagerSingleton::GetInstance()->GetCreditsMenu()->Enable();
				VideoPlayerAccessor::GetInstance()->PlayVideo(Enums::Video::Outro);
			}
			else
			{
				if (!myHasStoppedLevelMusic)
				{
					AudioManagerAccessor::GetInstance()->StopAllSounds();
					AudioManagerAccessor::GetInstance()->Play2D("Audio/PiratesOfTheBaltic_-_TheBootyMerchant.mp3", true, 0.2f);
					myHasStoppedLevelMusic = true;
				}
				MenuManagerSingleton::GetInstance()->GetShop()->Enable();
				
				if (myHasResetShop == false)
				{
					MenuManagerSingleton::GetInstance()->ResetShop();
					myHasResetShop = true;
				}
				MenuManagerSingleton::GetInstance()->SetNextLevelIndex(myCurrentLevel);
				MenuManagerSingleton::GetInstance()->GetHUD()->Disable();
			}
		}

		else
		{
			CheckIfLevelIsCleared();
			myHasResetShop = false;
			myHasStoppedLevelMusic = false;

			// Pack
			if (!myCurrentPack->ExitConditionIsMet())
			{
				myCurrentPack->Update();
			}
			else
			{

				int packSize = myPacks.size() - 1;

				if (myPackIndex < (packSize))
				{
					printf_s("changing to next pack from pack %i ...\n", myPackIndex + 1);
					myCurrentPack = myPacks[++myPackIndex];
					printf_s("Size of new pack: %i\n", myCurrentPack->myStoredEnemies.size());
				}
			}
			//Pu
			LevelLogic();
			// Check if Player cleared the level
		}
		if (myHasParticleOnMap)
		{
			myParticleEmitter->SpawnParticle();
			myParticleEmitter->Update();
		}
	}

	const std::string& LevelManager::CurrentLevelPath()
	{
		return myLevelPaths[myCurrentLevel];
	}

	void LevelManager::AddEnemy(Enemy* anEnemy)
	{
		printf_s("Recieved an enemy\n");
		myEnemies.push_back(anEnemy);
	}

	void LevelManager::SpawnBullet(const std::string& aType, VECTOR2F aPosition, const float aDamage)
	{
		Bullet* bullet = myBulletFactory->CreateBulletObject(aType, aPosition, aDamage);
		if (myPlayer->GetHasPenetratingRounds() && bullet->GetOwner() == Enums::BulletOwner::Player)
		{
			bullet->SetIsPenetrating();
		}
		myBullets.push_back(bullet);
	}

	void LevelManager::SpawnBullet(const std::string& aType, VECTOR2F aPosition, const VECTOR2F& aDirection, const float aDamage)
	{
		Bullet* bullet = myBulletFactory->CreateBulletObject(aType, aPosition, aDirection, aDamage);
		if (myPlayer->GetHasPenetratingRounds() && bullet->GetOwner() == Enums::BulletOwner::Player)
		{
			bullet->SetIsPenetrating();
		}
		myBullets.push_back(bullet);
	}

	bool LevelManager::LevelIsCleared()
	{
		return myLevelIsCleared;
	}

	void LevelManager::UpdateEnemies()
	{
		for (size_t i = 0; i < myEnemies.size(); i++)
		{

			myEnemies[i]->Update(Timer::GetInstance()->TGetDeltaTime());
			if (myEnemies[i]->GetCollider().Intersects(myPlayer->GetCollider()) && !myPlayer->GetHasCollided() && myEnemies[i]->GetIsTerrain())
			{
				//Om man vill att spelaren ska bouncea.
				/*myPlayer->Bounce(myEnemies[i]->GetPosition());
				if (myPlayer->GetIsShieldActive())
				{
					myPlayer->TakeShieldDamage(1);
				}
				else
				{
					myPlayer->TakeDamage(1.0f);
				}*/
				myPlayer->TakeDamage(10.f);
			}
			
			//If enemy collides with player, take shield damage first, if no shield, take normal damage.
			if (myEnemies[i]->GetCollider().Intersects(myPlayer->GetCollider()) && !myPlayer->GetHasCollided())
			{
				if (myPlayer->GetIsShieldActive())
				{
					myPlayer->TakeShieldDamage(1);
				}
				else
				{
					myPlayer->TakeDamage(1.0f);

					// Test
					RendererAccessor::GetInstance()->ShakeCamera(5.0f, 0.125f);
				}
			}
			if (myEnemies[i]->GetCollider().Intersects(myPlayer->GetCollider()) && !myPlayer->GetHasCollided() && myEnemies[i]->GetIsPopcorn())
			{
				myEnemies[i]->TakeDamage(100);
				CreateExplosionAt(myEnemies[i]->GetPosition());
				//My Player take damage, blow up mine
			}

			if (!myEnemies[i]->IsDead())
			{
				Studio::RendererAccessor::GetInstance()->Render(*myEnemies[i]);
			}

			if (myEnemies[i]->GetPosition().x < -50.0f || myEnemies[i]->GetPosition().y < -50.0f || myEnemies[i]->GetPosition().y > 1130.0f)
			{
				myEnemies.erase(myEnemies.begin() + i);
			}
		}

	}

	//Pu
	void LevelManager::LevelLogic()
	{
		UpdateEnemies();
		for (int i = myBullets.size() - 1; i >= 0; i--)
		{
			myBullets[i]->Update();
		}

		//Pu
		CheckCollision();

		for (int i = myBullets.size() - 1; i >= 0; i--)
		{
			if (myBullets[i]->GetPosition().x > 1920 || myBullets[i]->GetPosition().x < 0 || myBullets[i]->GetPosition().y < 0 || myBullets[i]->GetPosition().y > 1080)
			{
				myBullets[i]->ShouldDeleteThis(true);
				/*if (i != myBullets.size() - 1)
				{
					std::swap(myBullets[i], myBullets.back());
				}
				SAFE_DELETE(myBullets.back());
				myBullets.pop_back();*/
			}
		}

		// Remove bullets that's supposed to be deleted
		for (int i = myBullets.size() - 1; i >= 0; i--)
		{
			if (myBullets[i]->ShouldDeleteThis())
			{
				if ((i) != myBullets.size() - 1)
				{
					std::swap(myBullets[i], myBullets.back());
				}
				SAFE_DELETE(myBullets.back());
				myBullets.pop_back();
			}
			else
			{
				Studio::RendererAccessor::GetInstance()->Render(*myBullets[i]);
			}
		}

		for (int i = myEnemies.size() - 1; i >= 0; i--)
		{
			if (myEnemies[i]->IsDead())
			{
				myEnemies[i]->DeathLogic();
				CreateExplosionAt(myEnemies[i]->GetPosition());
				SAFE_DELETE(myEnemies[i]);
				myEnemies.erase(myEnemies.begin() + i);
			}
		}
		if (myPlayer->IsDead() && !myHasReloaded)
		{
			// Lägg till en meny här en callback eller liknande
			AudioManagerAccessor::GetInstance()->Play2D("Audio/Explosion.mp3", false, 0.1f);
			myHasReloaded = true;
			ReloadLevel();
		}
		UpdateExplosions();
		if (mySpawnedBoss && myBoss != nullptr)
		{
			myBoss->Update();

			if (myPlayer->Intersects(*myBoss))
			{
				myPlayer->Bounce(*myBoss->GetPosition());
				myPlayer->TakeDamage(1.0f);
			}
			if (myLaserIsFiring)
			{
				myLaser->Update(myBoss->GetPosition()->y);
				if (myPlayer->Intersects(*myLaser))
				{
					myPlayer->TakeDamage(myLaser->GetDamage());
				}
			}
		}
	}
	//Pu
	void LevelManager::CheckCollision()
	{
		if (mySpawnedBoss && myBoss != nullptr)
		{
			if (!myBoss->IsDead())
			{
				for (int i = myBullets.size() - 1; i >= 0; i--)
				{
					if (myBullets[i]->GetOwner() == Studio::Enums::BulletOwner::Player && myBoss->Intersects(*myBullets[i]) && myBullets[i]->IsEnemyAlreadyHit(myBoss) == false)
					{
						myBullets[i]->RegisterEnemyHit(myBoss);
						myBoss->HitLogic(myBullets[i]->GetDamage());
						myBullets[i]->Impact();
						myExplosions.push_back(new EffectExplosionLarge("sprites/Particles/impactSprite.dds", { 8,1 }, myBullets[i]->GetPosition()));
						if (myBullets[i]->GetIsPenetrating() == false)
						{
							myBullets.erase(myBullets.begin() + i);
						}
					}
				}
			}
			//When the boss dies?
			else
			{
				for (int i = 0; i < myEnemies.size(); i++)
				{
					CreateExplosionAt(myEnemies[i]->GetPosition());
				}
				myEnemies.clear();
				myBullets.clear();
				myBoss = nullptr;
			}
		}

		//Check if Player Hit
		if (!myBullets.empty())
		{
			for (int j = myBullets.size() - 1; j >= 0; j--)
			{
				if (myBullets[j]->GetOwner() == Studio::Enums::BulletOwner::Enemy && myPlayer->Intersects(*myBullets[j]))
				{
					if (myPlayer->GetIsShieldActive())
					{
						myPlayer->TakeShieldDamage(myBullets[j]->GetDamage());
					}
					else
					{
						myPlayer->TakeDamage(myBullets[j]->GetDamage());
					}
					//printf_s("Current Health: %f\n", myPlayer->GetCurrentHealth());
					myBullets[j]->Impact();
					myBullets.erase(myBullets.begin() + j);
				}
			}
		}

		//Check if Enemies Hit
		if (!myEnemies.empty() && !myBullets.empty())
		{
			for (int i = myEnemies.size() - 1; i >= 0; i--)
			{
				if (!myEnemies[i]->IsDead())
				{
					for (int j = myBullets.size() - 1; j >= 0; j--)
					{
						if (myBullets[j]->GetOwner() == Studio::Enums::BulletOwner::Player &&
							myEnemies[i]->Intersects(*myBullets[j]) &&
							myBullets[j]->IsEnemyAlreadyHit(myEnemies[i]) == false)
						{
							myBullets[j]->RegisterEnemyHit(myEnemies[i]);
							if (!myEnemies[i]->GetIsTerrain())
							{
								myEnemies[i]->TakeDamage(myBullets[j]->GetDamage());
							}
							myBullets[j]->Impact();

							if (myBullets[j]->GetIsPenetrating() == false)
							{
								myBullets.erase(myBullets.begin() + j);
							}
						}
					}
				}
			}

		}
	}

	void LevelManager::LoadLevel(int aLevelIndex)
	{
		ClearLevel();


		myCurrentLevel = aLevelIndex;
		myLevelIsCleared = false;

		rapidjson::Document document;

		std::string text;
		std::fstream file;
		file.open(myLevelPaths[myCurrentLevel]);
		{
			std::string line;
			while (std::getline(file, line))
			{
				text.append(line);
			}
		}
		file.close();
		document.Parse(text.c_str());

		if (document.HasMember("Packs"))
		{
			auto packs = document["Packs"].GetArray();

			printf_s("===JSON===\n%s\n==========\n", text.c_str());

			for (rapidjson::SizeType i = 0; i < packs.Size(); i++)
			{
				myPacks.push_back(new Pack(this, packs[i]));
			}

			myPackIndex = 0;
			myCurrentPack = myPacks[myPackIndex];
		}
		else
		{
			SETCONSOLECOLOR(CONSOLE_COLOR_RED);
			printf_s("ERROR: \"%s\" is missing packs\n", myLevelPaths[myCurrentLevel]);
			SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
		}
		if (myCurrentLevel >= myBackgroundManager->GetPathsSize() - 1)
		{
			myBackgroundManager->CreateBackground(myBackgroundManager->GetPathsSize() - 1);
		}
		else
		{
			myBackgroundManager->CreateBackground(myCurrentLevel);
		}
		myHasReloaded = false;
		// When to spawn Bossies
		if (myCurrentLevel == myLevelPaths.size() - 1)
		{
			myLevelBossSpawned = true;
		}
		mySpawnedBoss = false;
		MenuManagerSingleton::GetInstance()->GetShop()->Disable();
		MenuManagerSingleton::GetInstance()->GetHUD()->Enable();
		MenuManagerSingleton::GetInstance()->GetMainMenu()->Disable();
		MenuManagerSingleton::GetInstance()->GetPauseMenu()->Disable();

		//Song loading & Particle loading
		switch (myCurrentLevel)
		{
		case 0:
			SAFE_CREATE(myParticleEmitter, Studio::ParticleEmitter);
			AudioManagerAccessor::GetInstance()->Play2D("Audio/PiratesOfTheBalticLevel12Song.mp3", true, 0.17f);
			myParticleEmitter->Init(Studio::Enums::EParticleTypes::eSnow);
			myParticleEmitter->Activate();
			myHasParticleOnMap = true;
			break;
		case 1:
			SAFE_CREATE(myParticleEmitter, Studio::ParticleEmitter);
			AudioManagerAccessor::GetInstance()->Play2D("Audio/PiratesOfTheBalticLevel12Song.mp3", true, 0.17f);
			myParticleEmitter->Init(Studio::Enums::EParticleTypes::eSnow);
			myParticleEmitter->Activate();
			myHasParticleOnMap = true;
			break;
		case 2:
			AudioManagerAccessor::GetInstance()->Play2D("Audio/PiratesOfTheBalticLevel12Song.mp3", true, 0.17f);
			myHasParticleOnMap = false;
			break;
		case 3:
			SAFE_CREATE(myParticleEmitter, Studio::ParticleEmitter);
			AudioManagerAccessor::GetInstance()->Play2D("Audio/PiratesOfTheBalticLevel12Song.mp3", true, 0.17f);
			myParticleEmitter->Init(Studio::Enums::EParticleTypes::eRain);
			myParticleEmitter->Activate();
			myHasParticleOnMap = true;
			break;
		default:
			break;
		}


	}

	void LevelManager::ReloadLevel()
	{
		LoadLevel(myCurrentLevel);
		ScoreAccessor::GetInstance()->ResetScore();
		CoinAccessor::GetInstance()->ResetWorldCoins();
		for (int i = 0; i < myExplosions.size(); i++)
		{
			SAFE_DELETE(myExplosions[i]);
		}
		myExplosions.clear();
	}

	void LevelManager::ClearLevel()
	{
		ClearEnemies();
		ClearPacks();
		ClearBullets();
		SAFE_DELETE(myParticleEmitter);
		myBackgroundManager->ClearBackground();
		CoinAccessor::GetInstance()->ResetWorldCoins();
		myPlayer->ResetPlayerCurrentLevel();
		myBoss = nullptr;
	}

	const int LevelManager::GetCurrentLevelIndex() const { return myCurrentLevel; }

	const std::vector<std::string>& LevelManager::GetLevelPaths() const { return myLevelPaths; }

	void LevelManager::StopUpdating()
	{
		myIsUpdating = false;
	}

	void LevelManager::StartUpdating()
	{
		myIsUpdating = true;
	}

	bool LevelManager::IsLaserFiring()
	{
		return myLaserIsFiring;
	}

	void LevelManager::CheckIfLevelIsCleared()
	{

		if (myPackIndex == myPacks.size() - 1 && myEnemies.size() == 0 && myBoss == nullptr)
		{
			if (myLevelBossSpawned)
			{
				myBoss = myBossManager->GetLevelBoss(0);
				printf("Boss Spawned");
				myLevelBossSpawned = false;
				mySpawnedBoss = true;
			}
			else
			{
				myLevelIsCleared = true;
				myLevelEnemiesCleared = false;
				myLevelBossSpawned = false;
				/*if (myCurrentLevel >= myLevelPaths.size() - 1)
				{
					myCurrentLevel = myLevelPaths.size() - 1;
				}*/
				//else
				{
					CoinAccessor::GetInstance()->ResetWorldCoins();
					myCurrentLevel++;
				}
			}
		}
	}

	void LevelManager::UpdateExplosions()
	{
		for (int i = 0; i < myExplosions.size(); i++)
		{
			if (myExplosions[i]->IsAnimating())
			{
				myExplosions[i]->Update();
				RendererAccessor::GetInstance()->Render(*myExplosions[i]);
			}
			else
			{
				if (i != myExplosions.size() - 1)
				{
					std::swap(myExplosions[i], myExplosions.back());
				}
				SAFE_DELETE(myExplosions.back());
				myExplosions.pop_back();
			}
		}
	}

	void LevelManager::ClearEnemies()
	{
		for (int i = 0; i < myEnemies.size(); i++)
		{
			SAFE_DELETE(myEnemies[i]);
		}
		myEnemies.clear();
	}

	void LevelManager::ClearPacks()
	{
		for (int i = 0; i < myPacks.size(); i++)
		{
			SAFE_DELETE(myPacks[i]);
		}
		myPacks.clear();
	}

	void LevelManager::ClearBullets()
	{
		for (int i = 0; i < myBullets.size(); i++)
		{
			SAFE_DELETE(myBullets[i]);
		}
		myBullets.clear();
	}

	void LevelManager::SpawnMissile(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aExplosionRadius, const float aDamageAmount, const float aExplosionDamageAmount)
	{
		Missile* missile = myBulletFactory->CreateMissileObject(aOwner, aPosition, aExplosionRadius);
		myBullets.push_back(missile);
	}

	void LevelManager::SpawnAOEBullet(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aRadius)
	{
		auto aoeBullet = myBulletFactory->CreateAOEBullet(aOwner, aPosition, aRadius);
		myBullets.push_back(aoeBullet);
	}
	void LevelManager::SpawnTimedBomb(const Tga2D::Vector2f& aPosition, const Tga2D::Vector2f& aVelocity, const float aBlastRadius, const float aDamage)
	{
		auto bomb = myBulletFactory->CreateTimedBomb(aPosition, aVelocity, aBlastRadius, aDamage);
		myBullets.push_back(bomb);
	}
	void LevelManager::FireLaser(bool aChoice)
	{
		if (aChoice && myLaser == nullptr && myBoss != nullptr)
		{
			myLaser = new Laser(*myBoss->GetPosition());
			myLaserIsFiring = true;
		}
		if (!aChoice && myLaser != nullptr)
		{
			myLaserIsFiring = false;
			SAFE_DELETE(myLaser);
		}
	}
	void LevelManager::CreateExplosionAt(const Tga2D::Vector2f& aPosition, const float aRadius)
	{
		auto explosion = new EffectExplosionLarge("sprites/Particles/explosion_spritesheet.dds", { 8,1 }, aPosition);
		explosion->GetSpriteSheet().SetSize({ aRadius * 2 * 2, aRadius * 2 * 2 }); // Times 5 because the small explosion on the sprite
		myExplosions.push_back(explosion);
	}
}
