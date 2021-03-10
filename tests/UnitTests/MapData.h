#ifndef MAP_DATA_H
#define MAP_DATA_H

#include <vector>
#include <ostream>
#include <algorithm>

using namespace std;

class MapData
{
public:
   MapData ( int w, int h );
   MapData();

   int width;  /*!< The width value of the map */
   int height; /*!< The height value of the map */
   vector<int> map; /*!< The map with the opponents in it */
   vector<int> obstacleMap;
   vector<int> healthMap;
   vector<int> obsHealthMap;
   vector<int> actHealthMap;
};

#endif
