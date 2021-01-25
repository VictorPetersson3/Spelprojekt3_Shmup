#include "stdafx.h"
#include "Renderer.h"
#include <tga2d/sprite/sprite_batch.h>
#include <tga2d/sprite/sprite.h>
#include <set>

Renderer::~Renderer()
{
	for (auto& layers : myCoolMap)
	{
		for (auto& batch : layers.second)
		{
			SAFE_DELETE(batch.second);
		}
	}
}

void Renderer::Init()
{
	myWriteBuffer = &myBatchBuffer1;
	myReadBuffer = &myBatchBuffer2;
}

// LEGACY CODE - REMOVE ALL REFERENCES AS SOON AS POSSIBLE
// References found (1):
//    1. TestButton.cpp | Found in "void Update()"
void Renderer::RenderRenderCommand(Studio::RenderCommand aRenderCommand)
{
	SETCONSOLECOLOR(CONSOLE_COLOR_RED);
	printf_s("Renderer: OBSOLETE CODE CALLED! -> Renderer::RenderRenderCommand\n");
	SETCONSOLECOLOR(CONSOLE_COLOR_WHITE);
}

void Renderer::SwapBuffers()
{
	auto tempPointer = myReadBuffer;
	myReadBuffer = myWriteBuffer;
	myWriteBuffer = tempPointer;

	// Empty write buffer
	myWriteBuffer->clear();
}

void Renderer::Render(Studio::GameObject& aGameObject)
{
	// Write to buffer
	myWriteBuffer->push_back(aGameObject.GetSpriteSheet());
}

// Batching stuff
void Renderer::Render()
{
	// Move to own method
	for (auto& spriteSheet : *myReadBuffer)
	{
		// All sprites must have a file path.
		// If the current spriteSheet does not
		// contain one, give it one.
		if (spriteSheet.myImagePath.empty())
		{
			// Same as SpriteSheets safeguard constructor
			spriteSheet.myImagePath = "debugpixel";
			spriteSheet.mySize = { 100.0f, 100.0f };
		}

		// Create layer if it does not already exist
		myCoolMap[spriteSheet.myLayer];

		// Check if a batch with the same file path already exists on that layer
		if (myCoolMap.at(spriteSheet.myLayer).count(spriteSheet.myImagePath) == 0)
		{
			// It did not.
			// Create new batch
			auto batch = new Tga2D::CSpriteBatch(false);

			// Autoformat the path and init the batch
			std::string directory = "Sprites/";
			batch->Init(directory.append(spriteSheet.myImagePath).append(".dds").c_str());

			// Include the batch at correct layer
			myCoolMap.at(spriteSheet.myLayer)[spriteSheet.myImagePath] = batch;

			// Inform that a new spritebatch has been created
			SETCONSOLECOLOR(CONSOLE_COLOR_ONE_TIME);
			printf_s("Renderer: Created new SpriteBatch at layer %i with Sprite \"%s\"\n", spriteSheet.myLayer, spriteSheet.myImagePath.c_str());
			SETCONSOLECOLOR(CONSOLE_COLOR_NORMAL);
		}
	}

	// Sorting by Layers
	std::map<signed int, std::set<Tga2D::CSpriteBatch*>> filledLayeredBatches;

	// Add to batches
	for (auto& spriteSheet : *myReadBuffer)
	{
		if (myCoolMap.at(spriteSheet.myLayer).count(spriteSheet.myImagePath) > 0)
		{
			auto sprite = spriteSheet.mySprite;
			sprite->SetSizeRelativeToScreen({
				spriteSheet.mySize.x / SCREEN_HEIGHT, // Use height on both because
				spriteSheet.mySize.y / SCREEN_HEIGHT  // Tga2D is "special"
			});
			sprite->SetPosition({ spriteSheet.myPosition.x / SCREEN_WIDTH, spriteSheet.myPosition.y / SCREEN_HEIGHT });
			myCoolMap.at(spriteSheet.myLayer)[spriteSheet.myImagePath]->AddObject(sprite);
			
			// Used in sorting
			filledLayeredBatches[spriteSheet.myLayer].insert(myCoolMap.at(spriteSheet.myLayer).at(spriteSheet.myImagePath));
		}
	}

	// Render batches
	for (auto& layers : filledLayeredBatches)
	{
		for (auto& batch : layers.second)
		{
			batch->Render();
			batch->ClearAll();
		}
	}
}
