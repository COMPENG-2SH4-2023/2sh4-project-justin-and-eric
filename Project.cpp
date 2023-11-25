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
//global pointers for game mechanism and player class
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
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    
    //default created is 26 by 13
    ptrGameMechs = new GameMechs(26,13);//width = 26, height = 13
    ptrPlayer = new Player(ptrGameMechs);
    //the number of food is then set to 5
    ptrGameMechs->setNumFood(5);
    ptrGameMechs->generateFood(ptrPlayer->getPlayerPos());

}

void GetInput(void)
{   
    //needs to clear the current input if you dont press anything
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
    ptrPlayer->movePlayer();
    ptrPlayer->updatePlayerDir();
}

void DrawScreen(void)
{   
    MacUILib_clearScreen();  



    int hasprinted=1;

    //playerbody contains the player list
    objPosArrayList* playerBody = ptrPlayer->getPlayerPos();
    //tempbody for the current portion of the snake
    objPos tempBody;
    //foodpos for the current food 
    objPos foodpos;
 



    for (int i=0;i<ptrGameMechs->getBoardSizeY();i++){
        hasprinted=0;
        MacUILib_printf("\n");
        for(int j=0;j<ptrGameMechs->getBoardSizeX();j++){
            //has printed is for the spaces or empty portions of the screen. Without it, it would print spaces where other symbols were already printed
            hasprinted=0;

            for(int q = 0; q < playerBody->getSize(); q++)
            {
                playerBody->getElement(tempBody, q);
                if(tempBody.x == j && tempBody.y == i )
                {
                    //This break is because there iwll not be another player object in the same position, so theres not point of 
                    //iterating through the rest of the list
                    MacUILib_printf("%c", tempBody.symbol);
                    hasprinted = 1; 
                    break;
                }
            }
            //speeds up the loop as there will not be other symbols in the position of the player symbol anyways
            if(hasprinted) continue;


            
            if (i==0 || i==ptrGameMechs->getBoardSizeY()-1){
                MacUILib_printf("#");
            }
            if (i>0 && i<=ptrGameMechs->getBoardSizeY()-2){
                if (j==0 || j==ptrGameMechs->getBoardSizeX()-1){
                    MacUILib_printf("#");
                    hasprinted=1;
                }
                //This is for printing each food symbol in the list 
                //For loop for iterating through each object in the list
                for(int z=0;z<ptrGameMechs->getNumFood();z++){
                    ptrGameMechs->getFoodPos(foodpos,z);
                    if(j==foodpos.x && i==foodpos.y){
                        MacUILib_printf("%c",foodpos.symbol);
                        hasprinted = 1;
                    }
                }
                //if the important symbols have not printed, then it will print a space
                if(!hasprinted){
                    MacUILib_printf(" ");
                }
            }
        }
   }
   MacUILib_printf("\nScore: %d",ptrGameMechs->getScore());
   //craetes different prints depending on what the exit status is (lose, win, or just pressing space)
   if(ptrGameMechs->getExitFlagStatus()){
        MacUILib_clearScreen();
        if(ptrGameMechs->getWinStatus())
        {
            MacUILib_printf("\n you Win WWWW");
        }
        else if(ptrGameMechs->getloseFlagStatus())
        {
            MacUILib_printf("\n you lose LLLL");
        }
        else
        {
            MacUILib_printf("\n you Quit ):):):):");
        }
        MacUILib_printf("\n Bye [(>: )");
        MacUILib_Delay(9.99*DELAY_CONST);
        //This is one second for some reason (if you put 10 it goes to 1 idk)
   }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    //deletes the pointers to the class
    delete ptrGameMechs;
    delete ptrPlayer;
    MacUILib_clearScreen();    
    MacUILib_uninit();
}





