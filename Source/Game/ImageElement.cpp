#include "stdafx.h"
#include "ImageElement.h"
#include "RendererAccessor.h"
#include "Renderer.h"
#include "tga2d\sprite\sprite.h"

Studio::ImageElement::ImageElement(const char* aPath, VECTOR2F aPosition, VECTOR2F aSize, VECTOR2F aPivot, int aLayer, const char* aTag)
{
	mySpriteSheet = new SpriteSheet(aPath);
	mySpriteSheet->SetPivot(aPivot);
	mySpriteSheet->SetPosition(aPosition);
	mySpriteSheet->SetSizeRelativeToImage(aSize);
	mySpriteSheet->SetLayer(aLayer);

	tag = aTag;
}

Studio::ImageElement::ImageElement(const char* aPath, VECTOR2F aPosition, VECTOR2F aSize, VECTOR2F aPivot, int aLayer, const char* aTag, Tga2D::CColor aColor)
{
	mySpriteSheet = new SpriteSheet(aPath);
	mySpriteSheet->SetPivot(aPivot);
	mySpriteSheet->SetPosition(aPosition);
	mySpriteSheet->SetSizeRelativeToImage(aSize);
	mySpriteSheet->SetLayer(aLayer);
	mySpriteSheet->GetSprite()->SetColor(aColor);

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

void Studio::ImageElement::SetSprite(const char* aPath)
{
	mySpriteSheet->SetImagePath(aPath);
}

Studio::SpriteSheet* Studio::ImageElement::GetSpriteSheet()
{
	return mySpriteSheet;
}
