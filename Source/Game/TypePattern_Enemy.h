#pragma once

namespace Tga2D
{
	class CSprite;
}

class TypePattern_Enemy
{
public:
	TypePattern_Enemy(const std::string& aPath);
	~TypePattern_Enemy() = default;
	std::shared_ptr<Tga2D::CSprite> GetSprite();
private:
	std::shared_ptr<Tga2D::CSprite> mySprite;
};

