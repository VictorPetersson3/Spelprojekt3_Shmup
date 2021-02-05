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
#include "Pack.h"
#include "EnemyFactory.h"
#include "BulletFactory.h"
#include "Player.h"
#include "Boss.h"
#include "BossManager.h"
#include "BackgroundManager.h"
#include "EffectExplosionLarge.h"
#include "CoinAccessor.h"

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

namespace Studio
{
	LevelManager::LevelManager(BackgroundManager* aBackgroundManager, Player* aPlayer) :
		myBackgroundManager(aBackgroundManager),
		myPlayer(aPlayer)

	{
		SAFE_CREATE(myEnemyFactory, EnemyFactory());
		SAFE_CREATE(myBulletFactory, BulletFactory());
		SAFE_CREATE(myBoss, Boss("sprites/debugpixel.dds", { 1500.0f, 520.0f }, 1000.0f));
		myEnemyFactory->InitAllEnemyTypes();

		SAFE_CREATE(myBossManager, BossManager());

		//temp BulletFactory to try and spawn bullets via LevelManager -->Pu
		myBulletFactory->InitBulletType("sprites/debugpixel.dds", 12, "Enemy", -500.0f, Enums::BulletOwner::Enemy);
		myBulletFactory->InitBulletType("sprites/debugpixel.dds", 12, "Player", 800.0f, Enums::BulletOwner::Player);
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
		myLevelBossSpawned = false;
		myLevelEnemiesCleared = false;
		myLevelIsCleared = false;
		myHasReloaded = false;
	}

	LevelManager::~LevelManager()
	{
		myEnemyFactory->~EnemyFactory();
		SAFE_DELETE(myEnemyFactory);
		SAFE_DELETE_VECTOR(myPacks);
		SAFE_DELETE_VECTOR(myEnemies);
		SAFE_DELETE_VECTOR(myBullets);
		SAFE_DELETE_VECTOR(myExplosions);
		SAFE_DELETE(myBulletFactory);
		SAFE_DELETE(myBossManager);
		SAFE_DELETE(myBoss);
	}

	void LevelManager::Update()
	{

		if (myLevelIsCleared == true)
		{
			if (myCurrentLevel > myLevelPaths.size() - 1)
			{
				//StartCredits
			}
			else
			{
				MenuManagerSingleton::GetInstance()->GetShop()->Enable();
				MenuManagerSingleton::GetInstance()->SetNextLevelIndex(myCurrentLevel);
				MenuManagerSingleton::GetInstance()->GetHUD()->Disable();
			}
		}

		else
		{
			CheckIfLevelIsCleared();
			// Pack
			if (!myCurrentPack->ExitConditionIsMet())
			{
				myCurrentPack->Update();
			}
			else
			{
				if (myPackIndex < myPacks.size() - 1)
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

	void LevelManager::SpawnBullet(const std::string& aType, VECTOR2F aPosition)
	{
		Bullet* bullet = myBulletFactory->CreateBulletObject(aType, aPosition);
		if (myPlayer->HasPenetratingRounds() && bullet->GetOwner() == Enums::BulletOwner::Player)
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
				myPlayer->Bounce(myEnemies[i]->GetPosition());
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
				}
			}
			if (myEnemies[i]->GetCollider().Intersects(myPlayer->GetCollider()) && !myPlayer->GetHasCollided() && myEnemies[i]->GetIsPopcorn())
			{
				myEnemies[i]->TakeDamage(100);
				myExplosions.push_back(new EffectExplosionLarge("sprites/Particles/explosion_spritesheet.dds", { 8,1 }, myEnemies[i]->GetPosition()));
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
		// Copy & Paste from Jimmi
		for (Bullet* bullet : myBullets)
		{
			bullet->Update();

			Studio::RendererAccessor::GetInstance()->Render(*bullet);
		}

		for (int i = myBullets.size() - 1; i >= 0; i--)
		{
			if (myBullets[i]->GetPosition().x > 1920 || myBullets[i]->GetPosition().x < 0 || myBullets[i]->GetPosition().y < 0 || myBullets[i]->GetPosition().y > 1080)
			{
				if (i != myBullets.size() - 1)
				{
					std::swap(myBullets[i], myBullets.back());
					SAFE_DELETE(myBullets.back());
					myBullets.pop_back();
				}
			}
		}

		//Pu
		CheckCollision();

		// Remove bullets that's supposed to be deleted
		for (size_t i = 0; i < myBullets.size(); i++)
		{
			if (myBullets[i]->ShouldDeleteThis())
			{
				if (i != myBullets.size() - 1)
				{
					std::swap(myBullets[i], myBullets.back());
				}
				SAFE_DELETE(myBullets.back());
				myBullets.pop_back();
			}
		}

		for (int i = myEnemies.size() - 1; i >= 0; i--)
		{
			if (myEnemies[i]->IsDead())
			{
				myEnemies[i]->DeathLogic();
				myExplosions.push_back(new EffectExplosionLarge("sprites/Particles/explosion_spritesheet.dds", { 8,1 }, myEnemies[i]->GetPosition()));
				SAFE_DELETE(myEnemies[i]);
				myEnemies.erase(myEnemies.begin() + i);
			}
		}
		if (myPlayer->IsDead() && !myHasReloaded)
		{
			// Lägg till en meny här en callback eller liknande
			myHasReloaded = true;
			ReloadLevel();
		}
		UpdateExplosions();
		if (mySpawnedBoss && myBoss != nullptr)
		{
			myBoss->Update();
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
					if (myBullets[i]->GetOwner() == Studio::Enums::BulletOwner::Player && myBoss->Intersects(*myBullets[i]))
					{
						if (myBullets[i]->IsEnemyAlreadyHit(myBoss) == false)
						{
							myBullets[i]->RegisterEnemyHit(myBoss);
							myBoss->HitLogic(25.0f);
							myBullets[i]->Impact();

							if (myBullets[i]->GetIsPenetrating() == false)
							{
								myBullets.erase(myBullets.begin() + i);
							}
						}
					}
				}
			}
			//When the boss dies?
			else
			{
				for (int i = 0; i < myEnemies.size(); i++)
				{
					myExplosions.push_back(new EffectExplosionLarge("sprites/Particles/explosion_spritesheet.dds", { 8,1 }, myEnemies[i]->GetPosition()));
				}
				myEnemies.clear();
				myBullets.clear();
				myBoss = nullptr;
			}
		}
		if (!myBullets.empty())
		{
			for (int j = myBullets.size() - 1; j >= 0; j--)
			{
				if (myBullets[j]->GetOwner() == Studio::Enums::BulletOwner::Enemy)
				{
					if (myPlayer->Intersects(*myBullets[j]))
					{
						if (myPlayer->GetIsShieldActive())
						{
							myPlayer->TakeShieldDamage(1);
						}
						else
						{
							myPlayer->TakeDamage(1.0f);
						}
						//printf_s("Current Health: %f\n", myPlayer->GetCurrentHealth());
						myBullets[j]->Impact();
						myBullets.erase(myBullets.begin() + j);
					}
				}
			}
		}

		if (myEnemies.size() > 0)
		{
			if (myBullets.size() > 0)
			{
				for (int i = myEnemies.size() - 1; i >= 0; i--)
				{
					if (!myEnemies[i]->IsDead())
					{
						for (int j = myBullets.size() - 1; j >= 0; j--)
						{
							if (myBullets[j]->GetOwner() == Studio::Enums::BulletOwner::Player)
							{
								if (myEnemies[i]->Intersects(*myBullets[j]))
								{
									if (myBullets[j]->IsEnemyAlreadyHit(myEnemies[i]) == false)
									{
										myBullets[j]->RegisterEnemyHit(myEnemies[i]);
										if (!myEnemies[i]->GetIsTerrain())
										{
											myEnemies[i]->TakeDamage(100);
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
			}
		}
	}

	void LevelManager::LoadLevel(int aLevelIndex)
	{
		ClearLevel();
		SAFE_DELETE(myBoss);
		myBoss = nullptr;

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
		myBackgroundManager->ClearBackground();
		CoinAccessor::GetInstance()->ResetWorldCoins();
		myPlayer->ResetPlayerCurrentLevel();
	}

	const int LevelManager::GetCurrentLevelIndex() const { return myCurrentLevel; }

	const std::vector<std::string>& LevelManager::GetLevelPaths() const { return myLevelPaths; }

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
				if (myCurrentLevel >= myLevelPaths.size() - 1)
				{
					myCurrentLevel = myLevelPaths.size() - 1;
				}
				else
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

	void LevelManager::SpawnMissile(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aDirection)
	{
		switch (aOwner)
		{
		case Enums::BulletOwner::Player:
		{
			Missile* missile = myBulletFactory->CreateMissileObject(aOwner, aPosition, aDirection);
			myBullets.push_back(missile);
		}
		break;
		case Enums::BulletOwner::Enemy:
		{
			Missile* missile = myBulletFactory->CreateMissileObject(aOwner, aPosition, aDirection);
			myBullets.push_back(missile);
		}
		break;
		default:
			break;
		}

	}

	void LevelManager::SpawnAOEBullet(const Enums::BulletOwner& aOwner, const Tga2D::Vector2f& aPosition, const float aRadius)
	{
		auto aoeBullet = myBulletFactory->CreateAOEBullet(aOwner, aPosition, aRadius);
		myBullets.push_back(aoeBullet);
	}
}
