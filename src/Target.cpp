#include "Target.h"
#include <iostream>

Target::Target() {}
Target::~Target() {}

direction Target::move(MapData map, PositionData status)
{
    direction ret = STAY;
    return ret;
}

direction Target::attack(MapData map, PositionData status)
{
    direction ret = STAY;
    return ret;
}

attributes Target::setAttribute(int pointsAvailable, attributes baseStats)
{
   attributes tankAttributes;
   
   myStats = baseStats; 

   tankAttributes.tankHealth += pointsAvailable;

   return tankAttributes;
}

int Target::spendAP(MapData map, PositionData status)
{
    return 4; // just sit and reload
}

#ifdef DYNAMIC
extern "C" //required for runtime linking
{
    Actor * maker()
    {
        return new Target;
    }
}
#endif
