#pragma once
#include "GameObject.h"
namespace Studio
{
	class Coin : public GameObject
	{
	public:
		Coin(Tga2D::CSprite* aSprite, VECTOR2F aSpawnPosition);
		~Coin();

		int GetScoreValue();

		Studio::RenderCommand& GetRenderCommand();

	private:
		int myScoreValue;

		Tga2D::CSprite* mySprite;

		VECTOR2F myPosition;

	};
}


