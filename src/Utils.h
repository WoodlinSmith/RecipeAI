#ifndef UTILS_H
#define UTILS_H

#include "TankGraph.h"


node* buildNode(int objID);
nodeType assignType(int objID);
vector<int> getAdjacentIndices(int baseIndex, int mapWidth, int mapHeight);
pair<int,int> getCoords(int index, int mapWidth, int mapHeight);



#endif
