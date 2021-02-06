#pragma once
#include "UIElement.h"
#include "SpriteSheet.h"
#include <WinUser.h>

namespace Studio
{
    class SliderElement : public UIElement
    {
    public:
        SliderElement(const char* aSpritePath, const VECTOR2F& aPosition, const VECTOR2F& aSize, const int aLayer);
        ~SliderElement();

        void Update() override;
        
    private:
        SpriteSheet* mySpriteSheet;

        VECTOR2F mySize;

        float fillPercentage = 1.0f;

        float myLeft;
        float myRight;
        float myTop;
        float myBottom;

        HWND myWindowHandle;

    };
}


