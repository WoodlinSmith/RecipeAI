#include "Utils.h"

//Why can it not find this function
node* buildNode(int objID)
{
    node* graphNode = new (nothrow) node;
    graphNode->id=objID;
    graphNode->type=assignType(objID);
    graphNode->known=true;
    return graphNode;
}



nodeType assignType( int objID )
{
    nodeType type;

    if(objID==66)
        type=BUSH;
    else if (objID==67)
        type=CRATE;
    else if (objID==87)
        type=WATER;
    else if (objID==84)
        type=TREE;
    else if (objID==82)
        type=ROCK;
    else if (objID==0)
        type=EMPTY;
    else
        type=TANK;

    return type;
}

vector<int> getAdjacentIndices(int baseIndex, int mapWidth, int mapHeight)
{
    int topRow;
    int bottomRow;
    vector<int> adjIndices;
    for(int i=baseIndex-1;i<baseIndex+2;i++)
    {
        topRow=i-mapWidth;
        bottomRow=i+mapWidth;


        if(!topRow<0)
            adjIndices.push_back(topRow);
        if(!bottomRow>=mapWidth*mapHeight)
            adjIndices.push_back(bottomRow);
        if(!i<0 && !i>=mapWidth*mapHeight && i!=baseIndex)
            adjIndices.push_back(i);

    }
    return adjIndices;
}

pair<int,int> getCoords(int index, int mapWidth, int mapHeight)
{
    pair<int,int> coords;

    coords.first=index%mapWidth;

    //If the index is a factor the of the height, it will return an incorrect value (0)
    //Increment by 1 to ensure it is not a factor.
    coords.second=index%mapHeight;
    if(index%mapHeight==0&index!=0)
        coords.second=(index+1)%mapHeight;

    return coords;
}


