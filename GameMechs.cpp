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
    //default board x and board y
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
    //returns the current status of the exit flag
    return exitFlag;
}

char GameMechs::getInput()
{
    //returns the current input
    return input;
}

int GameMechs::getBoardSizeX()
{
    //returns the x size of the board
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    //returns the y size of the board
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    //sets the exit flag to true (this exits the game)
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    //sets input to the current input 
    input = this_input;
}

void GameMechs::clearInput()
{
    //clears the input (necessary as when you dont hold down the button the button pressed previously will persist)
    input = 0;
}

int GameMechs::getScore()
{
    //returns score 
    return score;
}
void GameMechs::incrementScore()
{
    //increments score by 1
    score+=1;
}
bool GameMechs::getloseFlagStatus()
{
    //gets the lost flag
    return loseFlag;
}

void GameMechs::setloseFlag()
{
    //set lose flag to true (means you lost)
    loseFlag = true;
    //it also then sets exit flag to true
    setExitTrue();
}

void GameMechs::setNumFood(int num)
{
    //Need to remove the foodlist when the numfood changes or else if it goes from big to small extra food in the list will remain
    if(numFood!=num){
        for(int i=0;i<numFood;i++)
            foodlist.removeHead();
    }
    numFood = num;
}
void GameMechs::generateFood(objPosArrayList* Blockoff)
{
    int xsymbol;
    int ysymbol;
    int symbol_on_x[boardSizeX-2];
    int symbol_on_y[boardSizeY-2];
    //bit vector implementation as explained by scott chen
    for(int i=0; i < boardSizeX-2;i++)
        symbol_on_x[i]=0;
    for(int i=0;i<boardSizeY-2;i++)
        symbol_on_y[i]=0;
    //This code is necessary to make sure the foodlist is empty before adding to it
    for(int i=0;i<numFood;i++)
        foodlist.removeHead();
    srand(time(NULL));
    for(int i=0;i<numFood;i++){
        //Adds a random food placement for the number of foods in the foodlist
            objPos currPlayerObj;
            bool conflict = false;
            do{
                conflict = false;
                xsymbol = rand()%(boardSizeX-2)+1;
                ysymbol = rand()%(boardSizeY-2)+1;
                //only on the last food in the list will there be the bonus food
                if(i<numFood-1)
                    foodpos.setObjPos(xsymbol,ysymbol,'%');
                else{
                    foodpos.setObjPos(xsymbol,ysymbol,'&');
                }
                for(int j=0;j<Blockoff->getSize();j++){
                    Blockoff->getElement(currPlayerObj,j);
                    //for each element in the food list, say if the position is equal to the previous food or if equal to player
                    //Then conflict is true
                    if(currPlayerObj.isPosEqual(&foodpos) || (symbol_on_x[xsymbol]==1 && symbol_on_y[ysymbol]==1))
                        conflict = true;
                }
            }
            while(conflict);
            //while loop is true when theres a conflict between player and food position
            //If while loop terminates, the current food is inserted into the head of the list
            foodlist.insertHead(foodpos);
            symbol_on_x[xsymbol]=1;
            symbol_on_y[ysymbol]=1;
    }

}

void GameMechs::getFoodPos(objPos &returnPos, int index)
{   
    //Basically does the same thing as the objPosArryList.cpp function
    foodlist.getElement(returnPos, index);
}

int GameMechs::getNumFood()
{
    //returns size of foodlist
    return foodlist.getSize();
}

bool GameMechs::getWinStatus()
{
    //returns for when winflag is true
    return winFlag;
}

void GameMechs::setWinStatusTrue()
{
    //sets the winflag is true
    winFlag = true;
}