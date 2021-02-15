#pragma once
#include <vector>
#include <array>
#include <unordered_map>
#include <map>
#include "GameObject.h"

// Batching stuff
typedef std::vector<Studio::SpriteSheet> SpriteSheetBuffer;

// Batching stuff
namespace Tga2D
{
	class CSpriteBatch;
}

namespace Studio
{
	class GameObject;
}

// Should Renderer not be a part of namespace Studio??
class Renderer
{
public:
	Renderer()
	{
		// Batching stuff
		myWriteBuffer = nullptr;
		myReadBuffer = nullptr;
	}
	~Renderer();
	void Init();
	void Render(Studio::GameObject& aGameObject);
	void Render(Studio::SpriteSheet& aSpriteSheet);
	void SwapBuffers();
	void Render(const float aDeltaTime = 1.0f / 60.0f);
	void ShakeCamera(const float aOomphValue, const float aDuration);

	// Legacy code
	void RenderRenderCommand(Studio::RenderCommand aRenderCommand);

private:
	void Update(float aDeltaTime);

	SpriteSheetBuffer myBatchBuffer1; // threading
	SpriteSheetBuffer myBatchBuffer2; // threading
	SpriteSheetBuffer* myWriteBuffer; // threading
	SpriteSheetBuffer* myReadBuffer;  // threading

	std::map // Map used for sorting purpses
	<
		signed int,			// Signed int for layers (-1 behind, 0 primary, 1 in front)
		std::unordered_map	// unordered_map since batches do not need to sorted at layer level
		<		 
			std::string,		 // String key to differentiate witch image to render
			Tga2D::CSpriteBatch* // SpriteBatch to reduce draw calls to the GPU
		>
	> myCoolMap; // myLayeredBatches

	float myOomph = 0.0f;
	float myShakeDuration = 1.0f;
	float _x = 0.0f, _y = 0.0f;
};

