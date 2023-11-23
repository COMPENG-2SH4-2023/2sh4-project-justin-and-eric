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
Player *ptrPlayer;
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

    objPos playerPos;
    ptrGameMechs = new GameMechs(26,13);//width = 26, height = 13
    ptrPlayer = new Player(ptrGameMechs);
    ptrGameMechs->setNumFood(5);
    ptrGameMechs->generateFood(playerPos);

}

void GetInput(void)
{   
    ptrGameMechs->clearInput();
    if(MacUILib_hasChar())
        ptrGameMechs->setInput(MacUILib_getChar());
}

void RunLogic(void)
{
    objPos playerPos;
    if(ptrGameMechs->getInput()==' '){
        ptrGameMechs->setExitTrue();
    }
    // if(ptrGameMechs->getInput()=='='){
    //     ptrGameMechs->incrementScore();
    // }
    if(ptrGameMechs->getInput()=='n')
    {
        ptrGameMechs->generateFood(playerPos);
    }
    ptrPlayer->movePlayer();
    ptrPlayer->updatePlayerDir();
}

void DrawScreen(void)
{   
    objPos playerPos;
    objPos foodpos;
    ptrPlayer->getPlayerPos(playerPos);

    MacUILib_clearScreen();    
    int hasprinted=1;
    for (int y=0;y<ptrGameMechs->getBoardSizeY();y++){
        hasprinted=0;
        MacUILib_printf("\n");
        for(int x=0;x<ptrGameMechs->getBoardSizeX();x++){
            hasprinted=0;
            if (y==0 || y==ptrGameMechs->getBoardSizeY()-1){
                MacUILib_printf("#");
            }
            if (y>0 && y<=ptrGameMechs->getBoardSizeY()-2){
                if (x==0 || x==ptrGameMechs->getBoardSizeX()-1){
                    MacUILib_printf("#");
                    hasprinted=1;
                }
                else if (x==playerPos.x && y==playerPos.y){
                    MacUILib_printf("%c",playerPos.symbol);
                    hasprinted=1;
                }
                for(int z=0;z<ptrGameMechs->getNumFood();z++){
                    ptrGameMechs->getFoodPos(foodpos,z);
                    if(x==foodpos.x && y==foodpos.y){
                        MacUILib_printf("%c",foodpos.symbol);
                        hasprinted = 1;
                    }
                }
                if(!hasprinted){
                    MacUILib_printf(" ");
                }
            }
        }
   }
   MacUILib_printf("\n%d, %d",playerPos.x,playerPos.y);
   
   
    if(ptrGameMechs->getloseFlagStatus())
    {
        MacUILib_printf("\n you lose LLLL");
        MacUILib_Delay(5*DELAY_CONST);
    }
    // for(int z=0;z<ptrGameMechs->getNumFood();z++){
    // ptrGameMechs->getFoodPos(foodpos,z);
    // MacUILib_printf("\n%d,%d, %d",foodpos.x,foodpos.y,playerPos.isPosEqual(&foodpos));
    // }
    // MacUILib_printf("\n%d, %d",ptrGameMechs->getBoardSizeX(),ptrGameMechs->getBoardSizeY());
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





