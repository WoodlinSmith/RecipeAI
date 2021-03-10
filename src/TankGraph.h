#ifndef TANKGRAPH_H
#define TANKGRAPH_H


#include <vector>
#include <list>
#include "MapData.h"
#include <unordered_map>
#include <iostream>

enum nodeType {EMPTY, TREE, ROCK, BUSH, CRATE, WATER, TANK};

struct node
{
    nodeType type = EMPTY;
    list<node*> adjList;
    int weight=-1;
    int id=-1;
    bool known=false;
};

//hash function adapted from the implementation provided at https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/
struct pairHash
{
    unsigned int operator() (const pair<int,int> &pair) const
    {
        auto hash1=hash<int>{}(pair.first);
        auto hash2=hash<int>{}(pair.second);
        return hash1^hash2;
    }
};

class tankGraph
{
    public:
        tankGraph();
        tankGraph(vector<int> obsMap, int mapWidth, int mapHeight);
        ~tankGraph();

        bool insertNode(node* graphNode, pair<int,int> coords);
        void buildAdjacency(int index, int mapWidth, int mapHeight);
        void weightGraph();
        void findShortestPath();//BFS

    private:
    unordered_map<pair<int,int>,node*,pairHash> nodeMap;

};



#endif