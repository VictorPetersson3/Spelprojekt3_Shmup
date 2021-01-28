#pragma once
#include "GameObject.h"
#include "Enums.h"

namespace Studio
{
	class TypePattern_Bullet;
	class Bullet : public GameObject
	{
	public:
		Bullet() = default;
		Bullet(VECTOR2F aPosition, TypePattern_Bullet* aTypePattern);
		~Bullet();
		void Update();

		VECTOR2F GetPosition();
		Enums::BulletOwner GetOwner();

	private:

		TypePattern_Bullet* myTypePattern;
		VECTOR2F myPosition;
	};
}


