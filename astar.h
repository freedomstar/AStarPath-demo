#ifndef ASTAR_H
#define ASTAR_H
#include "nodeitem.h"

class Astar
{
public:
    Astar(NodeItem *StarNode,NodeItem *EndNode,NodeItem *Map[20][20]);
    ~Astar();
    QList<NodeItem*>* AStarPath();
    QList<NodeItem*>* getNeibourhood(NodeItem *node);
    int getDistanceNodes(NodeItem *a, NodeItem *b);
    NodeItem *Map[20][20];
    NodeItem *StarNode;
    NodeItem *EndNode;
    QList<NodeItem*> *OpenSetList;
    QList<NodeItem*> *CloseSetList;
};

#endif // ASTAR_H
