#pragma once
#include "Game.h"

class CGame;

namespace Studio
{
    class GameAccessor
    {
    public:
        static GameAccessor& GetInstance();
    private:
        GameAccessor() = default;
        static GameAccessor ourInstance;
        CGame* myGame;
    public:
        GameAccessor(GameAccessor const&) = delete;
        void operator=(GameAccessor const&) = delete;

        CGame* GetGame();
        void SetGame(CGame* aGame);
    };


}