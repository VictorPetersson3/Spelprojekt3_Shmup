#pragma once
#include <map>

namespace Studio
{
	class Bullet;
	class TypePattern_Bullet;
	class BulletFactory
	{
	public:
		BulletFactory() = default;
		~BulletFactory();
		void InitBulletType(const std::string & aPath, const unsigned int aLayerOrder, const std::string & aType);
		Studio::Bullet* CreateBulletObject(const std::string & aType, float aSpeed, const Tga2D::Vector2f & aPosition);
	private:
		std::map<std::string, TypePattern_Bullet*> myBullets;
	};
}


