#include "MapData.h"

// This is a mocked out version of the MapData class that the game engine
// presents.  It is essentially just the data in the class.  None of the
// methods are implemented

MapData::MapData() {}

MapData::MapData(int w, int h) : width(w), height(h)
{
   map.resize(width*height, 0);
   obstacleMap.resize(width*height, 0);
   healthMap.resize(width*height, 0);
   obsHealthMap.resize(width*height, 0);
   actHealthMap.resize(width*height, 0);   
}
