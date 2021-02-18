#include "stdafx.h"
#include "EngineFlame.h"
#include "Timer.h"
#include "Renderer.h"
#include "RendererAccessor.h"

Studio::EngineFlame::EngineFlame(const char* aImagePath, const Tga2D::Vector2f& aAmountOfFrames, const Tga2D::Vector2f& aPosition):
	GameObject(aImagePath, aAmountOfFrames)
{
	GameObject::GetSpriteSheet().SetPivot({1.0, 0.5});
}

void Studio::EngineFlame::Update(int aCurrentState, const Tga2D::Vector2f& aPosition)
{
	//GameObject::SetFrame({ 1, static_cast<float>(aCurrentState)});
	Studio::RendererAccessor::GetInstance()->Render(*this);
	GameObject::Update(aPosition);
}

