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

void Renderer::Render(Studio::SpriteSheet& aSpriteSheet)
{
	myWriteBuffer->push_back(aSpriteSheet);
}

// Batching stuff
void Renderer::Render(const float aDeltaTime)
{
	// Move to own method
	for (auto& spriteSheet : *myReadBuffer)
	{
		// All sprites must have a file path.
		// If the current spriteSheet does not
		// contain one, give it one.
		if (spriteSheet.GetImagePath().empty())
		{
			// Same as SpriteSheets safeguard constructor
			spriteSheet.SetImagePath("sprites/debugpixel.dds");
			spriteSheet.GetSprite()->SetSizeRelativeToImage({ 100.0f, 100.0f });
		}

		// Create layer if it does not already exist
		myCoolMap[spriteSheet.GetLayer()];

		// Check if a batch with the same file path already exists on that layer
		if (myCoolMap.at(spriteSheet.GetLayer()).count(spriteSheet.GetImagePath()) == 0)
		{
			// It did not.
			// Create new batch
			auto batch = new Tga2D::CSpriteBatch(false);

			// Autoformat the path and init the batch
			

			//Not Type Safe Init of Sprite Batch
			batch->Init(spriteSheet.GetImagePath().c_str());
			
			// Include the batch at correct layer
			myCoolMap.at(spriteSheet.GetLayer())[spriteSheet.GetImagePath()] = batch;

			// Inform that a new spritebatch has been created
			SETCONSOLECOLOR(CONSOLE_COLOR_ONE_TIME);
			printf_s("Renderer: Created new SpriteBatch at layer %i with Sprite \"%s\"\n", spriteSheet.GetLayer(), spriteSheet.GetImagePath().c_str());
			SETCONSOLECOLOR(CONSOLE_COLOR_NORMAL);
		}
	}

	// Sorting by Layers
	std::map<signed int, std::set<Tga2D::CSpriteBatch*>> filledLayeredBatches;

	// Add to batches
	for (auto& spriteSheet : *myReadBuffer)
	{
		if (myCoolMap.at(spriteSheet.GetLayer()).count(spriteSheet.GetImagePath()) > 0)
		{
			auto sprite = spriteSheet.GetSprite();
			sprite->SetSizeRelativeToScreen({
				spriteSheet.GetSize().x / SCREEN_HEIGHT, // Use height on both because
				spriteSheet.GetSize().y / SCREEN_HEIGHT // Tga2D is "special"
			});
			sprite->SetPosition({ (spriteSheet.GetPosition().x + _x) / SCREEN_WIDTH, (spriteSheet.GetPosition().y + _y) / SCREEN_HEIGHT });

			//sprite->SetPosition(sprite->GetPosition() + VECTOR2F(aDeltaTime, aDeltaTime));

			myCoolMap.at(spriteSheet.GetLayer())[spriteSheet.GetImagePath()]->AddObject(sprite);
			
			// Used in sorting
			filledLayeredBatches[spriteSheet.GetLayer()].insert(myCoolMap.at(spriteSheet.GetLayer()).at(spriteSheet.GetImagePath()));
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

	Update(aDeltaTime);
}

void Renderer::ShakeCamera(const float aOomphValue, const float aDuration)
{
	myOomph = aOomphValue;
	myShakeDuration = 1.0f / aDuration;
}

void Renderer::Update(const float aDeltaTime)
{
	_x = (rand() % 5) * myOomph;
	_y = (rand() % 7) * myOomph;
	

	// dampen the oomph
	myOomph -= myOomph * myShakeDuration * aDeltaTime;

	// Prevent the shake to steer out of control
	if (myOomph < 0.0f)
	{
		myOomph = 0.0f;
	}
}