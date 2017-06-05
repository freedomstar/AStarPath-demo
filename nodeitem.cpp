#include "nodeitem.h"

NodeItem::NodeItem(int x,int y,bool isWall)
{
    this->x=x;
    this->y=y;
    this->isWall=isWall;
}

NodeItem::NodeItem(int x,int y)
{
    this->x=x;
    this->y=y;
}

int NodeItem:: fCost()
{
    return gCost+hCost;
}
