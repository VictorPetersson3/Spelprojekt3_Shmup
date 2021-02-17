#include "stdafx.h"
#include "Particle.h"
#include "stdafx.h"
#include "Timer.h"
#include "CommonUtilities/CURandom.h"
#include "CommonUtilities/CUMath.h"
#include "SpriteSheet.h"
#include "RendererAccessor.h"
#include "Renderer.h"
#include "tga2d/sprite/sprite.h"
#include "tga2d/engine.h"
#define PI (3.14159265358979323846f)
#define SCREENWIDTH static_cast<float>(Tga2D::CEngine::GetInstance()->GetWindowSize().x)
#define SCREENHEIGTH static_cast<float>(Tga2D::CEngine::GetInstance()->GetWindowSize().y)

Studio::Particle::Particle(const Enums::EParticleTypes aParticleType)
{
    mySprite = nullptr;
    myIsActive = false;
    myParticleType = aParticleType;
}

Studio::Particle::~Particle()
{
    SAFE_DELETE(mySprite);
}

void Studio::Particle::Init()
{
    //Common Variables
    float randomStartSize;
    float randomEndSize;
    float randomLifeTime;
    float randomVelocity;
    float randomRotation;
    myCurrentTime = 0;
    //TypeSpecific
    switch (myParticleType)
    {
    case Studio::Enums::EParticleTypes::eRain:
        //Sprite Specific
        mySprite = new Studio::SpriteSheet("sprites/particles/default_Particle.dds");
        mySprite->SetPivot({ 0.5, 0.5 });
        mySprite->GetSprite()->SetBlendState(EBlendState::EBlendState_Alphablend);
        //Life time, gravity and velocity
        randomLifeTime = CommonUtilities::GetRandomFloat(01.3, 2.5);
        randomVelocity = CommonUtilities::GetRandomFloat(850, 950.5);
        myGravity = 1.0;
        myVelocity = randomVelocity;
        myLifeTime = randomLifeTime;
        //Color
        myUse3Colors = true;
        myStartColor = Tga2D::CColor({ 0.5f, 0.6f, 0.6f, 0.2f });
        myMidColor = Tga2D::CColor({ 0.5f, 0.6f, 0.6f, 1.00f });
        myEndColor = Tga2D::CColor({ 0.5f, 0.6f, 0.6f, 0.3f });
        //Size
        myStartSize = Tga2D::Vector2f{ .008f , 0.6f };
        myEndSize = Tga2D::Vector2f{ 0.008f , 0.6f };
        mySprite->SetSizeRelativeToImage(myStartSize);
        mySprite->SetLayer(10);
        //Direction
        myDirection.x = -0.91f;
        myDirection.y = 0.50f;
        myDirection.Normalize();
        //Position
        myPosition.x = CommonUtilities::GetRandomFloat(500.0f, SCREENWIDTH + 200.0f);
        myPosition.y = CommonUtilities::GetRandomFloat(-20.0f, SCREENHEIGTH - 100.0f);
        //Wind
        myWindDirection = Tga2D::Vector2f{ -1.0f , 0.40f };
        myWindDirection.Normalize();
        myWindStrength = 0.51f;
        //Rotation
        myIsRotatingFollowDirection = true;
        //If Aboive true nothing else below does anything
        myRotation = (atan(myDirection.y / myDirection.x)) + PI * 0.5;
        myRotationSpeed = 1;
        myIsRotatingRandomDir = false;
        myRotationDirection = 0;
        if (myIsRotatingRandomDir)
        {
            myIsRotatingRandomDir = CommonUtilities::GetRandomFloat(-1, 1);
        }
        break;

    case Studio::Enums::EParticleTypes::eSnow:
        //Sprite Specific
        mySprite = new Studio::SpriteSheet("sprites/particles/default_Particle.dds");
        mySprite->SetPivot({ 0.5, 0.5 });
        mySprite->GetSprite()->SetBlendState(EBlendState::EBlendState_Alphablend);
        //Life time, gravity and velocity
        randomLifeTime = CommonUtilities::GetRandomFloat(2.0, 2.5);
        randomVelocity = CommonUtilities::GetRandomFloat(900.0, 1100.5);
        myGravity = 0.20;
        myVelocity = randomVelocity;
        myLifeTime = randomLifeTime;
        //Color
        myUse3Colors = true;
        myStartColor = Tga2D::CColor({ 0.8f, 0.8f, 0.9f, 0.20f });
        myMidColor = Tga2D::CColor({ 0.8f, 0.8f, 0.9f, 1.00f });
        myEndColor = Tga2D::CColor({ 0.8f, 0.8f, 0.9f, 0.0f });
        //Size
        myStartSize = Tga2D::Vector2f{ .04f , 0.04f };
        myEndSize = Tga2D::Vector2f{ 0.02f , 0.02f };
        mySprite->SetSizeRelativeToImage(myStartSize);
        //Direction
        myDirection.x = -0.91f;
        myDirection.y = 0.50f;
        myDirection.Normalize();
        //Position
        myPosition.x = CommonUtilities::GetRandomFloat(500.0f, SCREENWIDTH + 200.0f);
        myPosition.y = CommonUtilities::GetRandomFloat(-20.0f, SCREENHEIGTH - 100.0f);
        //Wind
        myWindDirection = Tga2D::Vector2f{ -1.0f , 0.40f };
        myWindDirection.Normalize();
        myWindStrength = 0.1f;
        //Rotation
        myIsRotatingFollowDirection = true;
        //If Above true nothing else below does anything
        myRotation = (atan(myDirection.y / myDirection.x)) + PI * 0.5;
        myRotationSpeed = 1;
        myIsRotatingRandomDir = false;
        myRotationDirection = 0;
        if (myIsRotatingRandomDir)
        {
            myIsRotatingRandomDir = CommonUtilities::GetRandomFloat(-1, 1);
        }
        break;
    default:
        break;
    }
}

const bool Studio::Particle::IsActive() const
{
    return myIsActive;
}

void Studio::Particle::SpawnParticle()
{
    myIsActive = true;
    Init();
}

void Studio::Particle::Update()
{
    myCurrentTime += Timer::GetInstance()->TGetDeltaTime();
    myPosition.x += myDirection.x * myVelocity * Timer::GetInstance()->TGetDeltaTime() + (myWindStrength * myWindDirection.x * Timer::GetInstance()->TGetDeltaTime());
    myPosition.y += myDirection.y * myVelocity * myGravity * Timer::GetInstance()->TGetDeltaTime() + (myWindStrength * myWindDirection.y * Timer::GetInstance()->TGetDeltaTime());
    myDirection.y += myGravity * Timer::GetInstance()->TGetDeltaTime();
    myDirection.x += (myWindStrength * myWindDirection.x * Timer::GetInstance()->TGetDeltaTime());
   
    if (myIsRotatingFollowDirection)
    {
        myRotation = (atan(myDirection.y / myDirection.x)) + PI * 0.5 * myRotationSpeed;
    }
    if (myIsRotatingRandomDir)
    {
        myRotation += Timer::GetInstance()->TGetDeltaTime() * myRotationSpeed * myRotationDirection;
    }
    if (myCurrentTime > myLifeTime)
    {
        myCurrentTime = 0;
        myIsActive = false;
    }
    //Size
    Tga2D::Vector2f currentSize;
    currentSize.x = CommonUtilities::Lerp(myStartSize.x, myEndSize.x, myCurrentTime / myLifeTime);
    currentSize.y = CommonUtilities::Lerp(myStartSize.y, myEndSize.y, myCurrentTime / myLifeTime);
    mySprite->SetSizeRelativeToImage(currentSize);
    UpdateColor();
    Render();
}

void Studio::Particle::UpdateColor()
{
    if (myUse3Colors)
    {
        if (myCurrentTime < myLifeTime * 0.5)
        {
            mySprite->SetColor({ CommonUtilities::Lerp(myStartColor.myR, myEndColor.myR, myCurrentTime / myLifeTime),
        CommonUtilities::Lerp(myStartColor.myG, myMidColor.myG, myCurrentTime / (myLifeTime * 0.5)),
        CommonUtilities::Lerp(myStartColor.myB, myMidColor.myB, myCurrentTime / (myLifeTime * 0.5)),
        CommonUtilities::Lerp(myStartColor.myA, myMidColor.myA, myCurrentTime / (myLifeTime * 0.5)) });
        }
        else
        {
            mySprite->SetColor({ CommonUtilities::Lerp(myStartColor.myR, myEndColor.myR, myCurrentTime / myLifeTime),
        CommonUtilities::Lerp(myMidColor.myG, myEndColor.myG, myCurrentTime / myLifeTime),
        CommonUtilities::Lerp(myMidColor.myB, myEndColor.myB, myCurrentTime / myLifeTime),
        CommonUtilities::Lerp(myMidColor.myA, myEndColor.myA, myCurrentTime / myLifeTime) });
        }
    }
    else
    {
        mySprite->SetColor({ CommonUtilities::Lerp(myStartColor.myR, myEndColor.myR, myCurrentTime / myLifeTime),
        CommonUtilities::Lerp(myStartColor.myG, myEndColor.myG, myCurrentTime / myLifeTime),
        CommonUtilities::Lerp(myStartColor.myB, myEndColor.myB, myCurrentTime / myLifeTime),
        CommonUtilities::Lerp(myStartColor.myA, myEndColor.myA, myCurrentTime / myLifeTime)
            });
    }
}

void Studio::Particle::Render()
{
    mySprite->SetRotation(myRotation);
    mySprite->SetPosition(myPosition);
    Studio::RendererAccessor::GetInstance()->Render(*mySprite);
}
