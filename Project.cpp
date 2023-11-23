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

    
    
    ptrGameMechs = new GameMechs(26,13);//width = 26, height = 13
    ptrPlayer = new Player(ptrGameMechs);

    ptrGameMechs->setNumFood(5);
    ptrGameMechs->generateFood(ptrPlayer->getPlayerPos());

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
    // if(ptrGameMechs->getInput()=='n')
    // {
    //     ptrGameMechs->generateFood(playerPos);
    // }
    ptrPlayer->movePlayer();
    ptrPlayer->updatePlayerDir();
}

void DrawScreen(void)
{   
    MacUILib_clearScreen();  



    int hasprinted=1;


    objPosArrayList* playerBody = ptrPlayer->getPlayerPos();
    objPos tempBody;

    objPos foodpos;
 



    for (int i=0;i<ptrGameMechs->getBoardSizeY();i++){
        hasprinted=0;
        MacUILib_printf("\n");
        for(int j=0;j<ptrGameMechs->getBoardSizeX();j++){
            hasprinted=0;

            for(int q = 0; q < playerBody->getSize(); q++)
            {
                playerBody->getElement(tempBody, q);
                if(tempBody.x == j && tempBody.y == i )
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    hasprinted = 1; 
                    break;
                }
            }

            if(hasprinted) continue;


            
            if (i==0 || i==ptrGameMechs->getBoardSizeY()-1){
                MacUILib_printf("#");
            }
            if (i>0 && i<=ptrGameMechs->getBoardSizeY()-2){
                if (j==0 || j==ptrGameMechs->getBoardSizeX()-1){
                    MacUILib_printf("#");
                    hasprinted=1;
                }

                for(int z=0;z<ptrGameMechs->getNumFood();z++){
                    ptrGameMechs->getFoodPos(foodpos,z);
                    if(j==foodpos.x && i==foodpos.y){
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
   
   
    if(ptrGameMechs->getloseFlagStatus())
    {
        MacUILib_printf("\n you lose LLLL");
        MacUILib_Delay(5*DELAY_CONST);
    }
    MacUILib_printf("\nwtf,%d",ptrGameMechs->getNumFood());
    for(int z=0;z<ptrGameMechs->getNumFood();z++){
    ptrGameMechs->getFoodPos(foodpos,z);
    MacUILib_printf("\nwtf%d,%d, ",foodpos.x,foodpos.y);
    }
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





