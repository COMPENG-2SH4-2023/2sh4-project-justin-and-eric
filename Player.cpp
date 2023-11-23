#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;



    // more actions to be included
    objPos currObj;
    currObj.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'*');
    playerPos.insertHead(currObj);
    

}


Player::~Player()
{
    // delete any heap members here
    //leave empty for now
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    objPos currObj;
    playerPos.getHeadElement(currObj);
    returnPos.setObjPos(currObj.x, currObj.y, currObj.symbol);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic       

    //Where is the input from? How do I check for inputs? 
    char input = mainGameMechsRef->getInput();

     switch (input)
     {
        case 'w':
        if(myDir != UP && myDir != DOWN)
        {
        myDir = UP;
        }
        break;

        case 'a':
        if(myDir != RIGHT && myDir != LEFT)
        {
        myDir = LEFT;
        }
        break;


        case 's':
        if(myDir != UP&& myDir != DOWN)
        {
        myDir = DOWN;
        }
        break;

        case 'd':
        if(myDir != LEFT && myDir != RIGHT)
        {
        myDir = RIGHT;
        }
        break;

        default:
        break;


     }
     input = 0 ; 
}

void Player::movePlayer()
{
    
    int bSizeX = mainGameMechsRef->getBoardSizeX();
    int bSizeY = mainGameMechsRef->getBoardSizeY();
    
    objPos currObj;
    getPlayerPos(currObj);
    // PPA3 Finite State Machine logic
    switch (myDir)
    {    
    case UP:
        currObj.y--;
        playerPos.insertHead(currObj);
        playerPos.removeTail();
        break;

    case DOWN:
        currObj.y ++;
        playerPos.insertHead(currObj);
        playerPos.removeTail();
        break;

    case LEFT:
        currObj.x --;
        playerPos.insertHead(currObj);
        playerPos.removeTail();
        break;

    case RIGHT:
        currObj.x ++;
        playerPos.insertHead(currObj);
        playerPos.removeTail();
        break;

    case STOP:
        break;

    default:
        break;
    }


    
    for(int i=0; i < playerPos.getSize(); i++)
    {
        playerPos.getElement(currObj, i);

    if (currObj.x == bSizeX)
    {
        currObj.x = 1;
    }

    if (currObj.x == 0)
    {
        currObj.x = bSizeX - 1;
    }
    
    if (currObj.y == 0)
    {
        currObj.y = bSizeY - 1;
    }

    if (currObj.y == bSizeY)
    {
        currObj.y = 1;
    }

    }


}

