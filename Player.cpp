#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    objPos currObj;  //declare a new variable currObj of type objPos


    // Initialize the currObj position to the center of the board, with the symbol *
    currObj.setObjPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'*');


    //declare the objPosArrayList contructor on the Heap, assigning it to the variable playerPosList
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(currObj); //Insert the currObj as the Head element of the newly declared playerPosList
    foodCountdown = 0;  //Initialize foodCountdown, for Special Case;


}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList; //delete the heap members declared in the previous function
    
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic       

    //declare new variable input, 
    //that is retrieved with the mainGameMechsRef pointer to the function in the GameMechs.cpp
    char input = mainGameMechsRef->getInput();


// The if conditions are to prevent 180deg turns as well as unneccessary proccessing
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
     input = 0 ;  //Reset input to 0 
}

void Player::movePlayer()
{
    //Border sizes retrieved
    int bSizeX = mainGameMechsRef->getBoardSizeX()-1;
    int bSizeY = mainGameMechsRef->getBoardSizeY()-1;

   //Collision Flags
    bool foodCollision = false;
    
    
    //Initialize current head element and get its values
    objPos currHead;  
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


    
  //Border Wrap around Logic
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



    //Collision Logic
    //For loop to iterate through every single Food element currently on the board
    for(int i=0;i< mainGameMechsRef->getNumFood();i++)
    {
        objPos currFood;
        mainGameMechsRef->getFoodPos(currFood,i);
        if(currHead.x == currFood.x && currHead.y == currFood.y){
            foodCollision= true;  //Set collision flag to true if collision occurs
            if(foodCountdown){ 
                foodCountdown--;  //Decrement foodCountdown if it has a non-zero value
            }
            //reason for no else statement is for these two to happen simultaneously at collision
            if(!foodCountdown){
                mainGameMechsRef->setNumFood(5);//When not special case, set number of foods on the board to 5
            }
            if(currFood.symbol == '&'){
                //If special food Gets eaten, set number of foods on the board to 25
                mainGameMechsRef->setNumFood(25);

             //When special collision occurs, set foodCountDown to 3, so that the SPecial effect lasts for 3 collisions
                foodCountdown = 3;
            }
        }
    }
    
    playerPosList->insertHead(currHead); //insert head to next position
    if(!foodCollision){ 
        //If no food was eaten, remove the tail as well to complete the movement
        playerPosList->removeTail();
    }
    else{
        //Otherwise (food eaten), genereate new food and increment the score
        mainGameMechsRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore();
    }


    //For loop that checks every element in the snake body
    for(int i=1;i<playerPosList->getSize();i++)
    {
        objPos BodyObj; //Declare variable BodyObj type objPos
        playerPosList->getElement(BodyObj, i);

        //Self collision logic, if head collides with any other body element, set lose flag
        if(currHead.x == BodyObj.x && currHead.y == BodyObj.y)
            mainGameMechsRef->setloseFlag();

    }
    

    //Win End-Game logic
    if(mainGameMechsRef->getScore() == ((mainGameMechsRef->getBoardSizeX()-2) * (mainGameMechsRef->getBoardSizeY()-2)-1)){
        mainGameMechsRef->setWinStatusTrue();
        mainGameMechsRef->setExitTrue();
    }
}



