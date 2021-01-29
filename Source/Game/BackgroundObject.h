#pragma once
#include "GameObject.h"
#include "rapidjson/document.h"

namespace Tga2D
{
	class CSprite;
}

namespace Studio
{
	class TypePattern_Background;
	class BackgroundObject : public GameObject
	{
	public:
		BackgroundObject(TypePattern_Background* aTypeObject, rapidjson::Value& aJsonObject);
		BackgroundObject(TypePattern_Background* aTypeObject, rapidjson::Value& aJsonObject, int aIndex);
		~BackgroundObject();
		void Update(float aDeltaTime);
		const Tga2D::Vector2f& GetPosition() const;
		void SetPosition(const Tga2D::Vector2f& aPosition);
		const bool GetIsTiling() const;
		const TypePattern_Background* GetTypeObject() const;

	private:
		TypePattern_Background* myTypeObject;
		float myScrollSpeed;
		bool myIsTiling;
	};
}
