#include "stdafx.h"
#include "LevelManager.h"
#include "rapidjson/document.h"
// Filhantering
#include <fstream>
#include <sstream>
// Spelfiler
#include "Timer.h"
#include "Enemy.h"

#include "RendererAccessor.h"
#include "Renderer.h"

#include <tga2d/sprite/sprite.h>

namespace Studio
{
	LevelManager::LevelManager()
	{
		LoadLevel("JSON/Levels/level_jimmi.json");
	}

	LevelManager::~LevelManager()
	{
		for (size_t i = 0; i < myEnemes.size(); i++)
		{
			SAFE_DELETE(myEnemes[i]);
		}
	}

	void LevelManager::Update()
	{
		for (size_t i = 0; i < myEnemes.size(); i++)
		{
			myEnemes[i]->Update(Studio::Timer::GetInstance()->TGetDeltaTime());
			Studio::RendererAccessor::GetInstance()->Render(*myEnemes[i]);
		}
	}

	void LevelManager::LoadLevel(const char* aLevelPath)
	{
		rapidjson::Document document;

		std::string text;
		std::fstream file;
		file.open(aLevelPath);
		{
			std::string line;
			while (std::getline(file, line))
			{
				text.append(line);
			}
		}
		file.close();
		document.Parse(text.c_str());

		auto enemies = document["Packs"].GetArray()[0]["Enemies"].GetArray();

		printf_s("===JSON===\n%s\n==========\n", text.c_str());

		for (rapidjson::SizeType i = 0; i < enemies.Size(); i++)
		{
			printf_s("Enemy Number %i\n", i + 1);

			auto pixel = new Tga2D::CSprite("Sprites/debugpixel.dds");
			pixel->SetSizeRelativeToImage({ 64, 64 });

			float x, y;

			x = 1.0f - enemies[i]["Position"]["X"].GetFloat() / 100.0f;
			y = 0.5f + enemies[i]["Position"]["Y"].GetFloat() / 100.0f;

			SAFE_CREATE(auto enemy, Studio::Enemy(pixel, { x, y }));

			myEnemes.push_back(enemy);
		}
	}
}
