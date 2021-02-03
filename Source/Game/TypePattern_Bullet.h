#pragma once
#include "Enums.h"

namespace Tga2D
{
	class CSprite;
}

namespace Studio
{
	class TypePattern_Bullet
	{
	public:
		TypePattern_Bullet(const std::string& aPath, const unsigned int aLayerOrder, const float aSpeed, const Enums::BulletOwner aOwner);
		~TypePattern_Bullet();

		const unsigned int GetLayerOrder() const;
		const std::string& GetImagePath();
		const float GetSpeed();
		const Enums::BulletOwner GetOwner();
		void SetOwner(const Enums::BulletOwner& aNewOwner);
	private:
		const unsigned int myLayerOrder;
		const std::string myImagePath;
		const float mySpeed;
		Enums::BulletOwner myOwner;
	};
}


