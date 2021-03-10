#include "Sentry.h"
#include <iostream>

Sentry::Sentry()
{
   srand(time(NULL));
}

Sentry::~Sentry() {}

bool validMove(MapData &map, int me, direction nextStep)
{
   if (nextStep == STAY) return false;
   int Row = me / map.width;
   int Col = me % map.width;

   Row += moveDirection[nextStep].first;
   Col += moveDirection[nextStep].second;
 
   if (!validRow(Row) || !validCol(Col) || !validCell(Row, Col)) return false;
   return true;
}

void Sentry::buildMoveStack()
{
   std::stack<direction> retVal;
   retVal.push(DOWN);
}

direction Sentry::move(MapData map, PositionData status)
{
    if (moveStack.empty()) buildMoveStack();

    direction move = moveStack.top() ; moveStack.pop();
    return move;
}

direction threatDirection(int me, int threat, int width)
{
   int rowOffset = (threat / width) - (me / width);
   int colOffset = (threat % width) - (me % width);

   if (rowOffset == 0) return (colOffset < 0) ? LEFT : RIGHT;
   if (colOffset == 0) return (rowOffset < 0) ? UP : DOWN;

   if (abs(rowOffset) == abs(colOffset))
   {
      if (rowOffset < 0 && colOffset < 0) return UPLEFT;
      if (rowOffset < 0 && colOffset > 0) return UPRIGHT;
      if (rowOffset > 0 && colOffset < 0) return DOWNLEFT;
      if (rowOffset > 0 && colOffset > 0) return DOWNRIGHT;
   }
   return STAY;
}

direction Sentry::attack(MapData map, PositionData status)
{
   int me = status.game_x + status.game_y * map.width;
   std::map<int,int>::iterator firstThreat = threats.begin();
   int threat = (*firstThreat).first;

   return threatDirection(me, threat, map.width);
}

attributes Sentry::setAttribute(int pointsAvailable, attributes baseStats)
{
   attributes tankAttributes;
  
   myAttributes = baseStats;
   myAttributes.tankRange += pointsAvailable; 
   tankAttributes.tankRange += pointsAvailable;

   return tankAttributes;
}

bool canAttackThreats() { return true; }

bool Sentry::threatDetected(MapData &map, PositionData &status)
{
   threats.clear();
   for (int vertex = 0 ; vertex < map.height * map.width ; vertex++)
   {
      int cell = map.map[vertex];
      if (cell == status.id || cell == -status.id) continue;
      if ((cell > 0 && cell <= 9) || cell < 0 && cell >= -9)
         threats[vertex] = cell;
   }

   return (threats.size() > 0);
}

int Sentry::attackOrMove(MapData &map, PositionData &status)
{
   if (threatDetected(map, status) && canAttackThreats())
      return ATTACK;

   return MOVE;
}

int Sentry::spendAP(MapData map, PositionData status)
{
    return attackOrMove(map, status);
}

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new Sentry;
    }
}
#endif
