#include "Turret.h"
#include <iostream>

const direction dirs[] = 
   {
      UP, UPRIGHT, RIGHT, DOWNRIGHT, DOWN, DOWNLEFT, LEFT, UPLEFT, STAY
   };

Turret::Turret() {}
Turret::~Turret() {}

direction Turret::move(MapData map, PositionData status)
{
    return STAY;
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

direction Turret::attack(MapData map, PositionData status)
{
   int me = status.game_x + status.game_y * map.width;
   for (auto &kv : threats)
   {
      direction dir = threatDirection(me, kv.first, map.width);
      if (dir != STAY)
         return dir;
   }

   return STAY;
}

attributes Turret::setAttribute(int pointsAvailable, attributes baseStats)
{
   baseStats.tankRadar += pointsAvailable;

   return baseStats;
}

bool Turret::threatDetected(MapData map, PositionData status)
{
   threats.clear();
   for (int vertex = 0 ; vertex < map.height * map.width ; vertex++)
   {
      int cell = map.map[vertex];
      if (cell == status.id || cell == -status.id) continue;
      if ((cell > 0 && cell <= 9) || (cell < 0 && cell >= -9))
         threats[vertex] = cell;
   }
   return (threats.size() > 0);
}

int Turret::spendAP(MapData map, PositionData status)
{
    return (threatDetected(map, status) ? ATTACK : DO_NOTHING);
}

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new Turret;
    }
}
#endif
