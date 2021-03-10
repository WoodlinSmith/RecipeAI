/**
 * @file
 * @brief
 * struct that contains the map and the dimensions of the field.
 */

#ifndef __MAP_DATA_H
#define __MAP_DATA_H

#include <vector>
#include <ostream>
#include <algorithm>

using namespace std;
/*******************************************************************//**
 * @author David Donahue
 *
 * @struct MapData
 * @par Description:
 * The map ADT for the platform
 *
 *
 **********************************************************************/
class MapData
{

	public:
		//void printMap ( vector<int> storedMap ); /*!< Print the specified map as a 2d ascii map */
		MapData ( int w, int h );
		MapData();
		void printMap ( vector<int> storedMap ); /*!< Print the specified map as a 2d ascii map */
		void moveActor ( int x, int y, int newX, int newY );
		int getActorID ( int x, int y );
		void setActor ( int x, int y, int id, int health );
		void removeActor ( int x, int y );
		int getActorHealth ( int x, int y );
		void setActorHealth ( int x, int y, int health );
		bool damageActor ( int x, int y, int damage );
		void setObstacle ( int x, int y, int id, int health );
		int getObstacleID ( int x, int y );
		int getObstacleHealth ( int x, int y );
		void setObstacleHealth ( int x, int y, int health );
		bool damageObstacle ( int x, int y, int damage );
		void removeObstacle ( int x, int y );
		bool outOfBounds ( int x, int y );
		void setHealthMap ( int x, int y, int health );

		MapData getMapSection ( int startX, int startY, int endX, int endY );


		int width;  /*!< The width value of the map */
		int height; /*!< The height value of the map */
		/** row-major-order list the ID's of anything on the tiles on the map (tanks, projectiles, and obstacles) */
		vector<int> map;
		// private:

		//These should be renamed for clarity, for the sake of preserving interface they have not
		/*!< row-major-order map of obstacles, first has obstacle ID, second has object health */
		vector<int> obstacleMap;
		vector<int> healthMap;
		vector<int> obsHealthMap;
		vector<int> actHealthMap;
};

/* overload << to display to console */
ostream &operator<< ( ostream &output, const MapData &mapInfo );

#endif
