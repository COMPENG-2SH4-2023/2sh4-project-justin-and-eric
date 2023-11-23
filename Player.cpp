#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;



    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'*');
}


Player::~Player()
{
    // delete any heap members here
    //leave empty for now
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
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
    // PPA3 Finite State Machine logic
    switch (myDir)
    {    
    case UP:
        playerPos.y --;
        break;

    case DOWN:
        playerPos.y ++;
        break;

    case LEFT:
        playerPos.x --;
        break;

    case RIGHT:
        playerPos.x ++;
        break;

    case STOP:
        break;

    default:
        break;
    }


    if (playerPos.x == bSizeX)
    {
        playerPos.x = 1;
    }

    if (playerPos.x == 0)
    {
        playerPos.x = bSizeX - 1;
    }
    
    if (playerPos.y == 0)
    {
        playerPos.y = bSizeY - 1;
    }

    if (playerPos.y == bSizeY)
    {
        playerPos.y = 1;
    }
}

