#include "stdafx.h"
#include "MousePointer.h"
#include "RendererAccessor.h"
#include "Renderer.h"
#include "tga2d/engine.h"

Studio::MousePointer::MousePointer() :
	GameObject("Sprites/UI/IGUI/IGUI_MousePointer.dds")
{
	mySpriteSheet.SetPivot({0.0f, 0.0f});
	mySpriteSheet.SetLayer(999999);
	mySpriteSheet.SetSizeRelativeToImage({0.5f, 0.5f});
	SetGodMode(true);
}

Studio::MousePointer::~MousePointer()
{
}

void Studio::MousePointer::Update(VECTOR2F aPosition)
{
	float ratio = 1920.f / static_cast<float>(Tga2D::CEngine::GetInstance()->GetWindowSize().x);
	GameObject::Update({ aPosition.x * ratio, aPosition.y * ratio });
	RendererAccessor::GetInstance()->Render(*this);
}
