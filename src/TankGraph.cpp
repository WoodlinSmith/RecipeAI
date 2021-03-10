#include "TankGraph.h"
#include "Utils.h"


tankGraph::tankGraph()
{

}

tankGraph::tankGraph(vector<int> obsMap, int mapWidth, int mapHeight)
{
    vector<int> adjIndices;
    node* newNode;
    pair<int,int> nodeCoords;

    //Creates and inserts nodes
    for(unsigned int i=0; i<obsMap.size(); i++)
    {
        newNode=buildNode(adjIndices[i]);
        nodeCoords=getCoords(i,mapWidth,mapHeight);
        if(!insertNode(newNode,nodeCoords))
            cout<<"Failed to insert node"<<endl;
        
    }

    //Creates adjacency list
    for(unsigned int i=0; i<obsMap.size();i++)
        buildAdjacency(i,mapWidth,mapHeight);
}



bool tankGraph::insertNode( node* graphNode,pair<int,int> coords)
{
     pair<pair<int,int>,node*> item;
     item.first=coords;
     item.second=graphNode;

     return nodeMap.insert(item).second;
}

void tankGraph::buildAdjacency(int index, int mapWidth, int mapHeight)
{
    
    vector<int> adjacIndices=getAdjacentIndices(index,mapWidth,mapHeight);
    pair<int,int> indexCoords=getCoords(index,mapWidth,mapHeight);
    pair<int,int> coords;

    
    for(unsigned int i=0; i<adjacIndices.size();i++)
    {
        coords=getCoords(i,mapWidth,mapHeight);
        nodeMap[indexCoords]->adjList.push_back(nodeMap[coords]);
    }

    
}