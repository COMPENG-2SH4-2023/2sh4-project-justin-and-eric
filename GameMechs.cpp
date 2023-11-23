#include "GameMechs.h"
#include "MacUILib.h"
GameMechs::GameMechs()
{
    input  = 0;
    score = 0;
    numFood=3;
    exitFlag = false;
    loseFlag = false;
    winFlag = false;
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
    winFlag = false;
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
    score+=24;
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
void GameMechs::generateFood(objPosArrayList* Blockoff)
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
            objPos currPlayerObj;
            bool conflict = false;
            do{
                conflict = false;
                xsymbol = rand()%(boardSizeX-2)+1;
                ysymbol = rand()%(boardSizeY-2)+1;
                foodpos.setObjPos(xsymbol,ysymbol,'%');
                for(int j=0;j<Blockoff->getSize();j++){
                    Blockoff->getElement(currPlayerObj,j);
                    if(currPlayerObj.isPosEqual(&foodpos) || (symbol_on_x[xsymbol]==1 && symbol_on_y[ysymbol]==1))
                        conflict = true;
                }
            }
            while(conflict);
            foodlist.insertHead(foodpos);
            // if(currPlayerObj.isPosEqual(&foodpos) || symbol_on_x[xsymbol]==1 && symbol_on_y[ysymbol]==1)
            //     foodlist.removeHead();
            symbol_on_x[xsymbol]=1;
            symbol_on_y[ysymbol]=1;
        
        
    }

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

bool GameMechs::getWinStatus()
{
    return winFlag;
}

void GameMechs::setWinStatusTrue()
{
    winFlag = true;
}