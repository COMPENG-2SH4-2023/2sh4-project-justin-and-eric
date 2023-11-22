#include "objPosArrayList.h"


// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
    
    aList = new objPos[sizeArray];    
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(sizeList == ARRAY_MAX_CAP){
        return;
    }

    for (int i = sizeList; i > 0 ; i--)
    {
        aList[i] = aList[i-1];
    }
    aList[0] = thisPos; 

    sizeList += 1;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(sizeList == ARRAY_MAX_CAP){
        return;
    }

    aList[sizeList++] = thisPos;
}

void objPosArrayList::removeHead()
{
    if (sizeList <= 0)
    {
        return;
    }
    
    for (int i = 0; i < sizeList - 1; i++)
    {
        aList[i] = aList[i + 1];
    }

    sizeList--;
}

void objPosArrayList::removeTail()
{
    if (sizeList <= 0)
    {
        return;
    }
    
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0].x, aList[0].y, aList[0].symbol);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList-1].x, aList[sizeList-1].y, aList[sizeList-1].symbol);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index].x, aList[index].y, aList[index].symbol);
}