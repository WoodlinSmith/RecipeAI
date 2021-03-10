#ifndef _RECIPE_AI_H
#define _RECIPE_AI_H


#include "Actor.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stack>


class RecipeAI : public Actor
{
    public:

        virtual direction move( MapData map, PositionData status);

        virtual direction attack ( MapData map, PositionData status);

        virtual attributes setAttribute( int pointsAvailable, attributes baseStats );

        virtual int spendAP( MapData map, PositionData status );

        RecipeAI();
        ~RecipeAI();

        attributes myStats;

        bool spend = false;
        bool safeMode = false;

    private:
        //MapData buildRadarMap(MapData gameMap, PositionData tankDat);
        bool getDir(direction dir, int &minDist, MapData map, PositionData status, int x, int y, direction &ret);
        bool checkNeighbouringCells ( int x, int y, MapData map, PositionData status );
        int calcDist ( int x1, int y1, int x2, int y2 );
        void genSafeMap(int x_val, int y_val, MapData map);
        void markCrates(int x, int y, MapData map);
        vector<int> getAdjacentIndices(int index, int mapWidth, int mapHeight);
        int getTargetIndex(vector<int> getAdjacentIndices, MapData &map, int index);
        bool validMove(int index, MapData &map);
        pair<int,int> getCoords(int index, int mapWidth, int mapHeight);
        direction convertCoordinatesToDirection(pair<int,int> targetLocation, pair<int,int> currentLocation);
        void genFullMap(MapData map);
        int countAdjacentUnknownNodes(int index, int mapWidth, int mapHeight);
        bool isStuck();
        int getHighestPriorityIndex(MapData &map);
        void buildAIPath(int currLoc, int targLoc, MapData &map);
        int findClosestAdjacentTile(int index, MapData &map, pair<int,int> currCoords);
        void updateData(MapData &map, PositionData status);
        void genLOSMap(MapData &map, PositionData status);


        //MapData radarMap;
        //vector<int> persistentMap;
        vector<int> safeMap;
        vector<int> recentVisited;
        vector<int> visitedAtLeastOnce;
        vector<int> fullMap;
        vector<int> turnsSinceVisit;
        vector<int> persObsMap;
        vector<int> losMap;
        stack<int> aiPath;

    
        int apCounter;
};

#endif
