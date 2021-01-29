#include "stdafx.h"
#include "ImageElement.h"
#include "RendererAccessor.h"
#include "Renderer.h"

Studio::ImageElement::ImageElement(const char* aPath, VECTOR2F aPosition, VECTOR2F aSize, VECTOR2F aPivot, int aLayer, const char* aTag)
{
	mySpriteSheet = new SpriteSheet(aPath);
	mySpriteSheet->SetPivot(aPivot);
	mySpriteSheet->SetPosition(aPosition);
	mySpriteSheet->SetSizeRelativeToImage(aSize);
	mySpriteSheet->SetLayer(aLayer);

	tag = aTag;
}

Studio::ImageElement::~ImageElement()
{
	delete mySpriteSheet;
	mySpriteSheet = nullptr;
}

void Studio::ImageElement::Update()
{
	if (myIsEnabled == true)
	{
		Studio::RendererAccessor::GetInstance()->Render(*mySpriteSheet);
	}
}
