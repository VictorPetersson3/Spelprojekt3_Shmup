#include "stdafx.h"
#include "Game_Accessor.h"

Studio::GameAccessor Studio::GameAccessor::ourInstance{};

Studio::GameAccessor& Studio::GameAccessor::GetInstance()
{
    return ourInstance;
}
CGame* Studio::GameAccessor::GetGame()
{
    return myGame;
}

void Studio::GameAccessor::SetGame(CGame* aGame)
{
    myGame = aGame;
}
