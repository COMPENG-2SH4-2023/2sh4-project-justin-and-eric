#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;



    // more actions to be included
    objPos currObj;

    currObj.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'*');


    playerPosList = new objPosArrayList();
    playerPosList->insertHead(currObj);
    playerPosList->insertHead(currObj);
    playerPosList->insertHead(currObj);
    playerPosList->insertHead(currObj);
    playerPosList->insertHead(currObj);


}


Player::~Player()
{
    // delete any heap members here
    //leave empty for now
    delete playerPosList;
    
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
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
    
    int bSizeX = mainGameMechsRef->getBoardSizeX()-1;
    int bSizeY = mainGameMechsRef->getBoardSizeY()-1;
    bool foodCollision = false;
    objPos currHead;
    
<<<<<<< HEAD
=======
    objPos currHead;
    
>>>>>>> b4c475d9350065b37f2236c62bc37d2c0b40a354
    playerPosList->getHeadElement(currHead);



    // PPA3 Finite State Machine logic
    switch (myDir)
    {    
    case UP:
        currHead.y--;
        break;

    case DOWN:
        currHead.y ++;
        break;

    case LEFT:
        currHead.x --;
        break;

    case RIGHT:
        currHead.x ++;
        break;

    case STOP:
        break;
    default:
        break;
    }


    

    if (currHead.x == bSizeX)
    {
        currHead.x = 1;
    }

    if (currHead.x == 0)
    {
        currHead.x = bSizeX - 1;
    }
    
    if (currHead.y == 0)
    {
        currHead.y = bSizeY - 1;
    }

    if (currHead.y == bSizeY)
    {
        currHead.y = 1;
    }
    for(int i=0;i<mainGameMechsRef->getNumFood();i++){
        objPos currFood;
        mainGameMechsRef->getFoodPos(currFood,i);
        if(currHead.x == currFood.x && currHead.y == currFood.y)
            foodCollision= true;
    }
    playerPosList->insertHead(currHead);
    if(!foodCollision){
        playerPosList->removeTail();
    }
    else{
        mainGameMechsRef->generateFood(currHead);
    }
    }




}

