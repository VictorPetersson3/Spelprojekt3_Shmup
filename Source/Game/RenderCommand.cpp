#include "stdafx.h"
#include <tga2d/sprite/sprite.h>
#include "RenderCommand.h"

namespace Studio
{
	RenderCommand::RenderCommand()
	{
		mySprite = nullptr;
	}
	RenderCommand::RenderCommand(Tga2D::CSprite* aSprite) :
		mySprite(aSprite)
	{
		myPosition = Tga2D::Vector2f::One;
		myRotation = 0;
		myScale = Tga2D::Vector2f::One;
	}

	RenderCommand::RenderCommand(Tga2D::CSprite* aSprite, const Tga2D::Vector2f& aSize) :
		mySprite(aSprite)
	{
		myPosition = Tga2D::Vector2f::One;
		myRotation = 0;
		SetScale(aSize);
	}

	RenderCommand::~RenderCommand()
	{
	}

	void RenderCommand::Update(const Tga2D::Vector2f& aPos)
	{
		myPosition = aPos;
		mySprite->SetPosition({ myPosition.x, myPosition.y });
	}

	void RenderCommand::Update(const Tga2D::Vector2f& aPos, Tga2D::CSprite* aSprite)
	{
		mySprite = aSprite;
		myPosition = aPos;
		mySprite->SetPosition({ myPosition.x, myPosition.y });
	}

	void RenderCommand::Update(Tga2D::CSprite* aSprite, const float aRotation)
	{
		mySprite = aSprite;
		myRotation += aRotation;
		mySprite->SetRotation(myRotation);
		mySprite->SetPosition({ myPosition.x, myPosition.y });
	}

	void RenderCommand::Update(const Tga2D::Vector2f& aPos, const float aRotation, Tga2D::CSprite* aSprite)
	{
		mySprite = aSprite;
		myPosition = aPos;
		mySprite->SetRotation(myRotation);
		mySprite->SetPosition({ myPosition.x, myPosition.y });
	}

	void RenderCommand::Render()
	{
		mySprite->SetPosition({ myPosition.x, myPosition.y });
		mySprite->Render();
	}

	void RenderCommand::SetScale(const Tga2D::Vector2f& aScale)
	{
		myScale = aScale;
		mySprite->SetSizeRelativeToImage(aScale);
	}

	Tga2D::CSprite* RenderCommand::GetSprite() const
	{
		return mySprite;
	}
}
