#ifndef __SENTRY_H
#define __SENTRY_H

#include "Actor.h"
#include "direction.h"
#include <cmath>
#include <map>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <algorithm>
#include <stack>

const direction dirs[] = {UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT, STAY};

const std::string dirStr[] =
{
   "UP", "UPRIGHT", "RIGHT", "DOWNRIGHT", "DOWN", "DOWNLEFT", "LEFT", "UPLEFT", "STAY"
};

#define Max(x, y) ((x) > (y) ? (x) : (y))
#define Min(x, y) ((x) < (y) ? (x) : (y))

const std::pair<int,int> moveDirection[] = {
   std::make_pair(-1,0), /* UP */
   std::make_pair(-1,1), /* UPRIGHT */
   std::make_pair(0,1),  /* RIGHT */
   std::make_pair(1,1),  /* DOWNRIGHT */
   std::make_pair(1,0),  /* DOWN */
   std::make_pair(1,-1), /* DOWNLEFT */
   std::make_pair(0,-1), /* LEFT */
   std::make_pair(-1,-1),/* UPLEFT */
   std::make_pair(0,0)
};

#define MOVE 1
#define ATTACK 2

#define REPEAT_LIMIT 10

#define validRow(r) ((r) >= 0 && (r) < map.height)
#define validCol(c) ((c) >= 0 && (c) < map.width)
#define validCell(r,c) (map.obstacleMap[r*map.width+c] == 'B' ||\
                        map.obstacleMap[r*map.width+c] == 0   ||\
                        map.obstacleMap[r*map.width+c] == 'C' ||\
                        map.obstacleMap[r*map.width+c] == 'T')
#define canEnter(r, c) (validRow(r) && validCol(c) && validCell(r,c))

class Sentry : public Actor
{
    std::map<int, int> threats;
    std::stack<direction> moveStack;
    attributes myAttributes;
    
public:
    virtual direction move(MapData map, PositionData status);
    virtual direction attack(MapData map, PositionData status);
    virtual attributes setAttribute(int pointsAvailable, attributes baseStats);
    virtual int spendAP(MapData map, PositionData status);
    Sentry();
    ~Sentry();

private:
    bool threatDetected(MapData&, PositionData&);
    int attackOrMove(MapData &, PositionData &);
    void buildMoveStack();

    friend class Observer;
};

#endif
