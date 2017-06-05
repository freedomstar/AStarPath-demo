#include "astar.h"
#include <cmath>
#include <QDebug>

Astar::Astar(NodeItem *StarNode,NodeItem *EndNode,NodeItem *Map[20][20])
{
    OpenSetList=new QList<NodeItem*>();
    CloseSetList=new QList<NodeItem*>();
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            this->Map[i][j]=Map[i][j];
        }
    }
    this->StarNode=StarNode;
    this->EndNode=EndNode;
}

QList<NodeItem*>* Astar::AStarPath()
{
    int y=0;
    NodeItem *curNode=StarNode;
    curNode->gCost=100;
    curNode->hCost=1000;
    while (1)
    {
        y++;
        if(OpenSetList->length()==0)
        {
            OpenSetList->append(curNode);
        }
        for(int i=0;i<OpenSetList->length();i++)
        {
            if(OpenSetList->value(i)->fCost()<curNode->fCost())
            {
                curNode=OpenSetList->value(i);
            }
        }
        if(curNode==EndNode)
        {
            break;
        }
        OpenSetList->removeOne(curNode);
        CloseSetList->append(curNode);

        QList<NodeItem*>* NeibourhoodList=getNeibourhood(curNode);
        if(y>1000||NeibourhoodList->length()<2)
        {
            break;
        }
        if(NeibourhoodList->length()<1)
            break;
        for(int i=0;i<NeibourhoodList->length();i++)
        {
            if(NeibourhoodList->value(i)->isWall||CloseSetList->contains(NeibourhoodList->value(i)))
                continue;
            NeibourhoodList->value(i)->hCost=getDistanceNodes(EndNode,NeibourhoodList->value(i));
            if(OpenSetList->contains(NeibourhoodList->value(i))&&curNode!=StarNode)
            {
                if(curNode->gCost+getDistanceNodes(curNode,NeibourhoodList->value(i))>NeibourhoodList->value(i)->gCost)
                {
                    curNode->gCost=curNode->gCost+getDistanceNodes(curNode,NeibourhoodList->value(i));
                }
            }
            else
            {
                NeibourhoodList->value(i)->gCost=getDistanceNodes(curNode,NeibourhoodList->value(i));
                NeibourhoodList->value(i)->parent=curNode;
                OpenSetList->append(NeibourhoodList->value(i));
            }
        }
    }

    QList<NodeItem*> *path=new QList<NodeItem*>();
    while (1)
    {
        if(curNode->parent!=StarNode)
        {
            path->append(curNode->parent);
            curNode=curNode->parent;
        }
        else
        {
            break;
        }
    }
    return path;
}


int Astar::getDistanceNodes(NodeItem *a, NodeItem *b)
{
//   return (int)sqrt((a->x-b->x)*(a->x-b->x)*10+(a->y-b->y)*(a->y-b->y));
    int cntX = abs(a->x - b->x);
    int cntY = abs(a->y - b->y);
    if (cntX > cntY)
    {
        return 14 * cntY + 10 * (cntX - cntY);
    } else {
        return 14 * cntX + 10 * (cntY - cntX);
    }
}


QList<NodeItem*>* Astar::getNeibourhood(NodeItem *node)
{
    QList<NodeItem*>* list = new QList<NodeItem*> ();
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)
                continue;
            int x = node->x + i;
            int y = node->y + j;
            if (x < 20 && x >= 0 && y < 20 && y >= 0)
            {
                list->append(Map[x][y]);
            }
        }
    }
    return list;
}

Astar:: ~Astar()
{

}
