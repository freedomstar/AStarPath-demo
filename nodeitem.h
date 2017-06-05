#ifndef NODEITEM_H
#define NODEITEM_H
#include <QPushButton>

class NodeItem
{
public:
    NodeItem(int x,int y,bool isWall);
    NodeItem(int x,int y);
    int x,y,gCost,hCost;
    bool isWall;
    NodeItem* parent;
    QPushButton *Button;
    int fCost();
};

#endif // NODEITEM_H
