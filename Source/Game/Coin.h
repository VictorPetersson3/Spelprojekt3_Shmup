#pragma once
#include "GameObject.h"
namespace Studio
{
	class Coin : public GameObject
	{
	public:
		Coin(VECTOR2F aSpawnPosition);
		void Update();
		int GetScoreValue();
		const float GetLifeTime() const;
		VECTOR2F GetPosition();
	private:
		int myScoreValue;
		float myLifeTime{};
		float mySpeed;
		VECTOR2F myPosition;

	};
}


