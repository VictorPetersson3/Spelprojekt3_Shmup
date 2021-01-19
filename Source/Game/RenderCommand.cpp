#include "stdafx.h"
#include <tga2d/sprite/sprite.h>
#include "RenderCommand.h"

namespace Studio
{
	RenderCommand::RenderCommand()
	{
		mySprite = nullptr;
		myPosition = Tga2D::Vector2f::One;
		myRotation = 0;
		myScale = Tga2D::Vector2f::One;
		myTextureRectTopLeft = Tga2D::Vector2f::Zero;
		myTextureRectBotRight = Tga2D::Vector2f::One;
	}
	RenderCommand::RenderCommand(Tga2D::CSprite* aSprite) :
		mySprite(aSprite)
	{
		myPosition = Tga2D::Vector2f::One;
		myRotation = 0;
		myScale = Tga2D::Vector2f::One;
		myTextureRectTopLeft = Tga2D::Vector2f::Zero;
		myTextureRectBotRight = Tga2D::Vector2f::One;
	}

	RenderCommand::RenderCommand(Tga2D::CSprite* aSprite, const Tga2D::Vector2f& aSize) :
		mySprite(aSprite)
	{
		myPosition = Tga2D::Vector2f::One;
		myRotation = 0;
		SetScale(aSize);
		myTextureRectTopLeft = Tga2D::Vector2f::Zero;
		myTextureRectBotRight = Tga2D::Vector2f::One;
	}

	RenderCommand::~RenderCommand()
	{
	}

	void RenderCommand::Update(const Tga2D::Vector2f& aPos)
	{
		myPosition = aPos;
	}

	void RenderCommand::Update(const Tga2D::Vector2f& aPos, Tga2D::CSprite* aSprite)
	{
		mySprite = aSprite;
		myPosition = aPos;
	}

	void RenderCommand::Update(Tga2D::CSprite* aSprite, const float aRotation)
	{
		mySprite = aSprite;
		myRotation += aRotation;
	}

	void RenderCommand::Update(const Tga2D::Vector2f& aPos, const float aRotation, Tga2D::CSprite* aSprite)
	{
		mySprite = aSprite;
		myPosition = aPos;
	}

	void RenderCommand::Update(const Tga2D::Vector2f& aPos, const Tga2D::Vector2f& aTexRecTopL, const Tga2D::Vector2f& aTexRecBotR)
	{
		myTextureRectTopLeft = aTexRecTopL;
		myTextureRectBotRight = aTexRecBotR;
		myPosition = aPos;
	}

	void RenderCommand::Render()
	{
		mySprite->SetTextureRect(myTextureRectTopLeft.x, myTextureRectTopLeft.y, myTextureRectBotRight.x, myTextureRectBotRight.y);
		mySprite->SetRotation(myRotation);
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
