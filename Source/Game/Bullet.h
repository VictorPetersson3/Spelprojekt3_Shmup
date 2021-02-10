#pragma once
#include "GameObject.h"
#include "Enums.h"
#include <vector>
namespace Studio
{
	class TypePattern_Bullet;
	class Bullet : public GameObject
	{
	public:
		Bullet();
		Bullet(VECTOR2F aPosition, TypePattern_Bullet* aTypePattern, const float aDamage);
		Bullet(const VECTOR2F& aPosition, const VECTOR2F& aDirection, TypePattern_Bullet* aTypePattern, const float aDamage);
		virtual ~Bullet();
		virtual void Update();
		virtual void Impact();

		void RegisterEnemyHit(GameObject* anEnemy);
		void SetIsPenetrating();
		float GetDamage();
		bool GetIsPenetrating();
		bool IsEnemyAlreadyHit(GameObject* anEnemy);
		VECTOR2F GetPosition();
		Enums::BulletOwner GetOwner() const;
		void SetOwner(const Enums::BulletOwner& aNewOwner);
		const bool ShouldDeleteThis() const;
		void ShouldDeleteThis(const bool aDeleteIt);

	protected:
		std::vector<GameObject*> myHitEnemies;
		TypePattern_Bullet* myTypePattern;
		float myDamage;
		bool myIsPenetrating = false;
		bool myHasDirection;
		VECTOR2F myPosition;
		VECTOR2F myDirection;
		bool myDeleteMeThisFrame = false;
	};
}


