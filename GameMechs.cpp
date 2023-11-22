#include "GameMechs.h"
#include "MacUILib.h"
GameMechs::GameMechs()
{
    input  = 0;
    score = 0;
    numFood=3;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    numFood=3;
    exitFlag = false;
    loseFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

int GameMechs::getScore()
{
    return score;
}
void GameMechs::incrementScore()
{
    score++;
}
bool GameMechs::getloseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setloseFlag()
{
    loseFlag = true;
    setExitTrue();
}

void GameMechs::setNumFood(int num)
{
    numFood = num;
}
void GameMechs::generateFood(objPos Blockoff)
{
    int xsymbol;
    int ysymbol;
    //foodpos = new objPos(getBoardSizeX(),getBoardSizeY(),'%');
    int symbol_on_x[boardSizeX-2];
    int symbol_on_y[boardSizeY-2];
    for(int i=0; i < boardSizeX-2;i++)
        symbol_on_x[i]=0;
    for(int i=0;i<boardSizeY-2;i++)
        symbol_on_y[i]=0;
    for(int i=0;i<numFood;i++)
        foodlist.removeHead();
    srand(time(NULL));
    for(int i=0;i<numFood;i++){
        do{
            xsymbol = rand()%(boardSizeX-2)+1;
            ysymbol = rand()%(boardSizeY-2)+1;
            foodpos.setObjPos(xsymbol,ysymbol,'%');
            foodlist.insertHead(foodpos);
            if(Blockoff.isPosEqual(&foodpos) || symbol_on_x[xsymbol]==1 && symbol_on_y[ysymbol]==1)
                foodlist.removeHead();
        }
        while(Blockoff.isPosEqual(&foodpos) || (symbol_on_x[xsymbol]==1 && symbol_on_y[ysymbol]==1));
        symbol_on_x[xsymbol]=1;
        symbol_on_y[ysymbol]=1;
    }
    // bool question = Blockoff.isPosEqual(&Blockoff);
    // int a,i=0,xsymbol,ysymbol;
    // int vector[size], vectorx[width], vectory[height];
    // // This is possibly one of the most conceptually challenging function in all PPAs
    // // Once you've mastered this one, you are ready to take on the 2SH4 course project!
    
    // // Random Non-Repeating Item Generation Algorithm
    // ////////////////////////////////////////////////////
    // for(i=0;i<size;i++){
    //     vector[i]=0;
    // }
    // for(i=0;i<width;i++){
    //     vectorx[i]=0;
    // }
    // for(i=0;i<height;i++){
    //     vectory[i]=0;
    // }
    // for(i=0;i<62;i++){
    //     vector_alphanumeric[i]=0;
    // }
    // // Use random number generator function, rand(), to generate a random x-y coordinate and a random choice of character from the Goal String as the ASCII character symbol.
    // //      The x and y coordinate range should fall within the xRange and yRange limits, which should be the x- and y-dimension of the board size.
    // // This will then be a candidate of the randomly generated Item to be placed on the game board.
    // srand(time(NULL));
    // for(i=0;i<listSize;i++){
    //     if(i<2){
    //         do{
    //         a = rand()%my_strlen(str);  
    //         xsymbol = rand()%xRange+1;
    //         ysymbol = rand()%yRange+1;
    //         }
    //         while(vector[a]==1 || (vectorx[xsymbol-1]==1 && vectory[ysymbol-1]==1) || (xsymbol==playerPos->x && ysymbol == playerPos->y));
    //         vectorx[xsymbol-1]=1;
    //         vectory[ysymbol-1]=1;
    //         vector[a] =1;
        
    //         list[i].symbol = *(str+a);
    //         list[i].x=xsymbol;
    //         list[i].y=ysymbol;
    //     }
    //     else{
    //         do{
    //             a=rand()%62;
    //             xsymbol = rand()%xRange+1;
    //             ysymbol = rand()%yRange+1;
    //         }
    //         while(vector_alphanumeric[a]==1 || (a+55)==list[0].symbol || (a+55)==list[1].symbol || (a+61)==list[0].symbol || (a+61)==list[1].symbol ||(vectorx[xsymbol-1]==1 && vectory[ysymbol-1]==1) || (xsymbol==playerPos->x && ysymbol == playerPos->y));
    //         vector_alphanumeric[a]=1;
    //         vectorx[xsymbol-1]=1;
    //         vectory[ysymbol-1]=1; 

    //         if(a<10){
    //             list[i].symbol=a+48;
    //         }
    //         else if(a<36){
    //             list[i].symbol=a+55;
    //         }
    //         else{
    //             list[i].symbol=a+61;
    //         }
    //         list[i].x=xsymbol;
    //         list[i].y=ysymbol;
    //     }
    // }
}

void GameMechs::getFoodPos(objPos &returnPos, int index)
{   
    
    //returnPos.setObjPos(foodpos.x,foodpos.y,foodpos.symbol);
    foodlist.getElement(returnPos, index);
}

int GameMechs::getNumFood()
{
    return foodlist.getSize();
}