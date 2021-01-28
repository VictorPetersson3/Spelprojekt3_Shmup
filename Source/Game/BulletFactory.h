#pragma once
#include <map>
#include "Enums.h"

namespace Studio
{
	class Bullet;
	class TypePattern_Bullet;
	class BulletFactory
	{
	public:
		BulletFactory() = default;
		~BulletFactory();
		void InitBulletType(const std::string & aPath, const unsigned int aLayerOrder, const std::string & aType, float aSpeed, Enums::BulletOwner aBulletOwner);
		Studio::Bullet* CreateBulletObject(const std::string & aType, const Tga2D::Vector2f & aPosition);
	private:
		std::map<std::string, TypePattern_Bullet*> myBullets;
	};
}


