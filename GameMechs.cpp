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
            foodlist.removeTail();
    }
    numFood = num;
}
void GameMechs::generateFood(objPosArrayList* Blockoff)
{   
    bool stopRandomise = false;
    int emptySpaces = (boardSizeX-2) * (boardSizeY-2)-score-1;
    int xsymbol=0;
    int ysymbol=0;
    // Dynamic allocation is when you say new int, but this is just a local array that will be deleted
    int symbol_on_xy[boardSizeX][boardSizeY];
    //bit vector implementation as explained by scott chen
    // Although this time you need a 2d array
    for(int i=0; i < boardSizeX;i++){
        for(int j=0;j<boardSizeY;j++){
            symbol_on_xy[i][j]=0;
        }
    }
    //This code is necessary to make sure the foodlist is empty before adding to it
    for(int i=0;i<numFood;i++)
        foodlist.removeTail();
    //For when there is more food than what is permitted on the screen
    if(numFood>emptySpaces){
        numFood = emptySpaces;
        stopRandomise=true;
        // Will stop items from being randomised on the board because a: theres no point as there are the same number of food for eadch space and b: it wastes a lo of time trying to find the spaces where a player is not located
    }
    srand(time(NULL));
    for(int i=0;i<numFood;i++){
        //Adds a random food placement for the number of foods in the foodlist
            objPos currPlayerObj;
            objPos foodpos;
            // Conflict variable for when the player and the food item is in contact with one another
            bool conflict = false;
            if(!stopRandomise){
                // This only runs when the objects are supposed to be randomised
                do{
                    conflict = false;
                    // Same code as PPA3, it generates items randomly on the board
                    xsymbol = rand()%(boardSizeX-2)+1;
                    ysymbol = rand()%(boardSizeY-2)+1;
                    //only on the last food in the list will there be the bonus food
                    if(i<numFood-1)
                        foodpos.setObjPos(xsymbol,ysymbol,'%');
                    else{
                        foodpos.setObjPos(xsymbol,ysymbol,'&');
                    }
                    // The above are the symbols for the food types where the & only occurs only once as it is the bonus food
                    for(int j=0;j<Blockoff->getSize();j++){
                        Blockoff->getElement(currPlayerObj,j);
                        //for each element in the food list, say if the position is equal to the previous food or if equal to player
                        //Then conflict is true
                        if(currPlayerObj.isPosEqual(&foodpos) || (symbol_on_xy[xsymbol][ysymbol]==1)){
                            conflict = true;
                            // If the current generate food item is in contact with another food item or with the current player object, then a conflict will occur and the while loop will not terminate
                        }
                    }
                }
                while(conflict);
                //while loop is true when theres a conflict between player and food position
                //If while loop terminates, the current food is inserted into the head of the list
            }
            else{
                // These lines onlt get called when there is more food items than empty spaces
                for(xsymbol =1;xsymbol<(boardSizeX-1);xsymbol++){
                    for(ysymbol =1;ysymbol<(boardSizeY-1);ysymbol++){
                        // Instead of randomly generating x and y symbol, it goes across the board
                        conflict=false;
                        foodpos.setObjPos(xsymbol,ysymbol,'%');
                        for(int j=0;j<Blockoff->getSize();j++){
                            Blockoff->getElement(currPlayerObj,j);
                            // If the current index corresponds to a previous food item or with the player, it will skip
                            if(currPlayerObj.isPosEqual(&foodpos)|| (symbol_on_xy[xsymbol][ysymbol]==1))
                                conflict = true;
                            // Same type of code as before
                        }
                        // Both for loops automatically terminates when there is no conflict as there is not point in iterating through the rest of the board if the previous if statement had completely passed.
                        if(!conflict)
                            break;
                    }   
                    if(!conflict)
                        break;
                }
            }
        //    Setting array to one as explained by scotty
            symbol_on_xy[xsymbol][ysymbol]=1;
            foodlist.insertTail(foodpos);
            // You can do insert tail or insert head as they are both adding an object to the list, but in this case insert tail was used just because
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