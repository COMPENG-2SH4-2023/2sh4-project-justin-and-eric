#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        
        int boardSizeX;
        int boardSizeY;

        int score;
        bool loseFlag;

        objPos foodpos;
        objPosArrayList foodlist;
        int numFood;
    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        bool getExitFlagStatus();
        void setExitTrue();

        char getInput();
        void setInput(char this_input);
        void clearInput();
        void incrementScore();
        bool getloseFlagStatus();
        void setloseFlag();

        int getBoardSizeX();
        int getBoardSizeY();
        int getScore();
        
        void generateFood(objPos Blockoff); //Need to upgrade this
        void getFoodPos(objPos &returnPos, int index);
        int getNumFood();
        void setNumFood(int num);

};

#endif