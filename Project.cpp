#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

GameMechs *ptrGameMechs;


int main(void)
{

    Initialize();

    while(ptrGameMechs->getExitFlagStatus() == false)  
    {   
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
        //ptrGameMechs->setExitTrue();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    ptrGameMechs = new GameMechs(26,13);//width = 26, height = 13
}

void GetInput(void)
{

}

void RunLogic(void)
{
    if(ptrGameMechs->getInput()==' '){
        ptrGameMechs->setExitTrue();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
    MacUILib_printf(" %d, %d",ptrGameMechs->getBoardSizeX(),ptrGameMechs->getBoardSizeY());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    delete ptrGameMechs;
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
