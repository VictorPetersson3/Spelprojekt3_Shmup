#pragma once
#include <map>
#include "TypePattern_Bullet.h"

namespace Studio
{
	class Bullet;
	class BulletFactory
	{
	public:
		BulletFactory() = default;
		~BulletFactory();
		void InitBulletType(const std::string & aPath, const unsigned int aLayerOrder, const std::string & aType);
		Studio::Bullet* CreateBulletObject(const std::string& aType, const Tga2D::Vector2f& aPosition, const float& aSpeed);
	private:
		std::map<std::string, TypePattern_Bullet*> myBulletObjects;
	};
}


