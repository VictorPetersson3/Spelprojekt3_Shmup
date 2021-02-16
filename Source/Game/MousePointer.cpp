#include "stdafx.h"
#include "MousePointer.h"
#include "RendererAccessor.h"
#include "Renderer.h"

Studio::MousePointer::MousePointer() :
	GameObject("Sprites/UI/IGUI/IGUI_MousePointer.dds")
{
	mySpriteSheet.SetPivot({0.0f, 0.0f});
	mySpriteSheet.SetLayer(999999);
	SetGodMode(true);
}

Studio::MousePointer::~MousePointer()
{
}

void Studio::MousePointer::Update(VECTOR2F aPosition)
{
	GameObject::Update(aPosition);
	RendererAccessor::GetInstance()->Render(*this);
}
