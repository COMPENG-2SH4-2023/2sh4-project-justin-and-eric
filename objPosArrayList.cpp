#include "objPosArrayList.h"


// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    sizeList = 0; 
    sizeArray = ARRAY_MAX_CAP; //ARRAY_MAX_CAP defined as 256
    
    aList = new objPos[sizeArray]; // declare a new List on the heap with the size 256
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; //Destructor for the heap members
}

int objPosArrayList::getSize()
{
    return sizeList; //Returns size of the List
}

void objPosArrayList::insertHead(objPos thisPos)
{
    //If sizeList equal to maximum array number, no more space to insert new head -> return
    if(sizeList == ARRAY_MAX_CAP){
        return;
    }

    //Shift every single element back by one index 
    for (int i = sizeList; i > 0 ; i--)
    {
        aList[i] = aList[i-1];
    }

    //Then insert new Head element to the start of the List
    aList[0] = thisPos; 

    //INcrement the size of List by 1
    sizeList += 1;
}

void objPosArrayList::insertTail(objPos thisPos)
{
     //If sizeList equal to maximum array number, no more space to insert new tail -> return
    if(sizeList == ARRAY_MAX_CAP){
        return;
    }

    //Insert the tail as the last element of the List, while incrementing sizeList by  1
    aList[sizeList++] = thisPos;
}


void objPosArrayList::removeHead()
{
    //If sizeList is lesser than or equal to 0, no element to remove -> return
    if (sizeList <= 0)
    {
        return;
    }
    
    //Shift every element of the list forward by one index
    for (int i = 0; i < sizeList - 1; i++)
    {
        aList[i] = aList[i + 1];
    }

    //decrement sizeList
    sizeList--;
}

void objPosArrayList::removeTail()
{
    //If sizeList is lesser than or equal to 0, no element to remove -> return
    if (sizeList <= 0)
    {
        return;
    }
    
    //Decrement sizeList, the last element no longer a part of the list
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    //return the x value, y value, and the symbol of the head element
    returnPos.setObjPos(aList[0].x, aList[0].y, aList[0].symbol);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    //return the x value, y value, and the symbol of the tail element
    returnPos.setObjPos(aList[sizeList-1].x, aList[sizeList-1].y, aList[sizeList-1].symbol);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    //return the x value, y value, and the symbol of element at the index
    returnPos.setObjPos(aList[index].x, aList[index].y, aList[index].symbol);
}
