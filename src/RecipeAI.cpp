#include "RecipeAI.h"

RecipeAI::RecipeAI()
{
	apCounter = 0;
	for(int i=0; i<5000; i++)
		fullMap.push_back(0);
}
RecipeAI::~RecipeAI() {}


/**
 * @author Woodlin Smith and Mangesh Sakordekar
 * @par Description:
 * Calculates where to move based on whether or not
 * it needs to move to a safe space, LOS space, or 
 * map exploration
 * @param[in] map - The current state of the playfield
 * @param[in] status - The AI's tank's location, health and ID
 * @return direction to move
 */
direction RecipeAI::move ( MapData map, PositionData status )
{
	int x, y;
	direction ret = STAY;
	int xpos = status.game_x, ypos = status.game_y;
	int index=ypos*map.width+xpos;
	int targetIndex;
	vector<int> adjacentIndices;

	//Safe mode finds a position on the map with laest number of tanks attacking
	if(safeMode)
	{
		safeMap.clear();
		for(unsigned int i=0;i<map.map.size();i++)
		{
			safeMap.push_back(0);
		}

		for ( x = 0; x < map.width; ++x )
			for ( y = 0; y < map.height; ++y )

				if ( (map.map[x + y * map.width] || map.obstacleMap[x + y * map.width]=='C')//if there is an actor at X, Y
					&& map.map[x + y * map.width] != status.id //And it is not you
					&& map.map[x + y * map.width] != -status.id )//And it is not your projectile
				{
					if(map.obstacleMap[x + y * map.width]=='C')
						markCrates(x,y, map);
					else
						genSafeMap(x,y, map);
				}

		int min = safeMap[xpos+ + ypos * map.width];
		if ( xpos+1 < map.height && safeMap[(xpos+1) + ypos * map.width] < min && !map.map[(xpos+1) + ypos * map.width]
			&& ( !map.obstacleMap[(xpos+1) + ypos * map.width] // check for obstacle
			|| map.obstacleMap[(xpos+1) + ypos * map.width] == 'T'
			|| map.obstacleMap[(xpos+1) + ypos * map.width] == 'B' ))
		{
			ret = RIGHT;
			min = safeMap[(xpos+1) + ypos * map.width];
		}

		if ( xpos-1 >= 0 && safeMap[(xpos-1) + ypos * map.width] < min && !map.map[(xpos-1) + ypos * map.width]
			&& ( !map.obstacleMap[(xpos-1) + ypos * map.width] // check for obstacle
			|| map.obstacleMap[(xpos-1) + ypos * map.width] == 'T'
			|| map.obstacleMap[(xpos-1) + ypos * map.width] == 'B' ))
		{
			ret = LEFT;
			min = safeMap[(xpos-1) + ypos * map.width];
		}

		if ( ypos-1 >= 0 && safeMap[xpos + (ypos-1) * map.width] < min && !map.map[xpos + (ypos-1) * map.width]
			&& ( !map.obstacleMap[xpos + (ypos-1) * map.width] // check for obstacle
			|| map.obstacleMap[xpos + (ypos-1) * map.width] == 'T'
			|| map.obstacleMap[xpos + (ypos-1) * map.width] == 'B' ))
		{
			ret = UP;
			min = safeMap[xpos + (ypos-1) * map.width];
		}

		if ( ypos+1 < map.width && safeMap[xpos + (ypos+1) * map.width] < min && !map.map[xpos + (ypos+1) * map.width]
			&& ( !map.obstacleMap[xpos + (ypos+1) * map.width] // check for obstacle
			|| map.obstacleMap[xpos + (ypos+1) * map.width] == 'T'
			|| map.obstacleMap[xpos + (ypos+1) * map.width] == 'B' ))
		{
			ret = DOWN;
			min = safeMap[xpos + (ypos+1) * map.width];
		}

		if ( xpos+1 < map.height && ypos-1 >= 0 && safeMap[(xpos+1) + (ypos-1) * map.width] < min && !map.map[(xpos+1) + (ypos-1) * map.width]
			&& ( !map.obstacleMap[(xpos+1) + (ypos-1) * map.width] // check for obstacle
			|| map.obstacleMap[(xpos+1) + (ypos-1) * map.width] == 'T'
			|| map.obstacleMap[(xpos+1) + (ypos-1) * map.width] == 'B' ))
		{
			ret = UPRIGHT;
			min = safeMap[(xpos+1) + (ypos-1) * map.width];
		}

		if ( xpos+1 < map.height && ypos+1 < map.width && safeMap[(xpos+1) + (ypos+1) * map.width] < min && !map.map[(xpos+1) + (ypos+1) * map.width]
			&& ( !map.obstacleMap[(xpos+1) + (ypos+1) * map.width] // check for obstacle
			|| map.obstacleMap[(xpos+1) + (ypos+1) * map.width] == 'T'
			|| map.obstacleMap[(xpos+1) + (ypos+1) * map.width] == 'B' ))
		{
			ret = DOWNRIGHT;
			min = safeMap[(xpos+1) + (ypos+1) * map.width];
		}

		if ( xpos-1 >= 0 && ypos+1 < map.width && safeMap[(xpos-1) + (ypos+1) * map.width] < min && !map.map[(xpos-1) + (ypos+1) * map.width]
			&& ( !map.obstacleMap[(xpos-1) + (ypos+1) * map.width] // check for obstacle
			|| map.obstacleMap[(xpos-1) + (ypos+1) * map.width] == 'T'
			|| map.obstacleMap[(xpos-1) + (ypos+1) * map.width] == 'B' ))
		{
			ret = DOWNLEFT;
			min = safeMap[(xpos-1) + (ypos+1) * map.width];
		}

		if ( xpos-1 >= 0 && ypos-1 < map.width && safeMap[(xpos-1) + (ypos-1) * map.width] < min && !map.map[(xpos-1) + (ypos-1) * map.width]
			&& ( !map.obstacleMap[(xpos-1) + (ypos-1) * map.width] // check for obstacle
			|| map.obstacleMap[(xpos-1) + (ypos-1) * map.width] == 'T'
			|| map.obstacleMap[(xpos-1) + (ypos-1) * map.width] == 'B' ))
		{
			ret = UPLEFT;
			min = safeMap[(xpos-1) + (ypos-1) * map.width];
		}

		return ret;
	}


	x = (status.game_x-myStats.tankRadar < 0) ? 0 : status.game_x-myStats.tankRadar;
	for ( ; x < map.width && x <= (status.game_x+myStats.tankRadar); ++x )
	{
		y = (status.game_y-myStats.tankRadar < 0) ? 0 : status.game_y-myStats.tankRadar;
		for ( ; y < map.height && y <= (status.game_y+myStats.tankRadar); ++y )
		{
			//If an enemy is encountered closer than previously encountered
			if ( map.map[x + y * map.width] > 0 &&
			        map.map[x + y * map.width] != status.id &&!safeMode )
			{
				losMap.clear();
				safeMap.clear();
				for(unsigned int i=0;i<map.map.size();i++)
				{
					losMap.push_back(0);
					safeMap.push_back(0);
				}
				genSafeMap(x,y, map);
				genLOSMap(map,status);

			if ( xpos+1 < map.height && !losMap[(xpos+1) + ypos * map.width] && !map.map[(xpos+1) + ypos * map.width]
				&& ( !map.obstacleMap[(xpos+1) + ypos * map.width] // check for obstacle
				|| map.obstacleMap[(xpos+1) + ypos * map.width] == 'T'
				|| map.obstacleMap[(xpos+1) + ypos * map.width] == 'B' ))
			{
				ret = RIGHT;
			}

			if ( xpos-1 >= 0 && !losMap[(xpos-1) + ypos * map.width] && !map.map[(xpos-1) + ypos * map.width]
				&& ( !map.obstacleMap[(xpos-1) + ypos * map.width] // check for obstacle
				|| map.obstacleMap[(xpos-1) + ypos * map.width] == 'T'
				|| map.obstacleMap[(xpos-1) + ypos * map.width] == 'B' ))
			{
				ret = LEFT;
			}

			if ( ypos-1 >= 0 && !losMap[xpos + (ypos-1) * map.width] && !map.map[xpos + (ypos-1) * map.width]
				&& ( !map.obstacleMap[xpos + (ypos-1) * map.width] // check for obstacle
				|| map.obstacleMap[xpos + (ypos-1) * map.width] == 'T'
				|| map.obstacleMap[xpos + (ypos-1) * map.width] == 'B' ))
			{
				ret = UP;
			}

			if ( ypos+1 < map.width && !losMap[xpos + (ypos+1) * map.width] && !map.map[xpos + (ypos+1) * map.width]
				&& ( !map.obstacleMap[xpos + (ypos+1) * map.width] // check for obstacle
				|| map.obstacleMap[xpos + (ypos+1) * map.width] == 'T'
				|| map.obstacleMap[xpos + (ypos+1) * map.width] == 'B' ))
			{
				ret = DOWN;
			}

			if ( xpos+1 < map.height && ypos-1 >= 0 && !losMap[(xpos+1) + (ypos-1) * map.width] && !map.map[(xpos+1) + (ypos-1) * map.width]
				&& ( !map.obstacleMap[(xpos+1) + (ypos-1) * map.width] // check for obstacle
				|| map.obstacleMap[(xpos+1) + (ypos-1) * map.width] == 'T'
				|| map.obstacleMap[(xpos+1) + (ypos-1) * map.width] == 'B' ))
			{
				ret = UPRIGHT;
			}

			if ( xpos+1 < map.height && ypos+1 < map.width && !losMap[(xpos+1) + (ypos+1) * map.width] && !map.map[(xpos+1) + (ypos+1) * map.width]
				&& ( !map.obstacleMap[(xpos+1) + (ypos+1) * map.width] // check for obstacle
				|| map.obstacleMap[(xpos+1) + (ypos+1) * map.width] == 'T'
				|| map.obstacleMap[(xpos+1) + (ypos+1) * map.width] == 'B' ))
			{
				ret = DOWNRIGHT;
			}

			if ( xpos-1 >= 0 && ypos+1 < map.width && !losMap[(xpos-1) + (ypos+1) * map.width] && !map.map[(xpos-1) + (ypos+1) * map.width]
				&& ( !map.obstacleMap[(xpos-1) + (ypos+1) * map.width] // check for obstacle
				|| map.obstacleMap[(xpos-1) + (ypos+1) * map.width] == 'T'
				|| map.obstacleMap[(xpos-1) + (ypos+1) * map.width] == 'B' ))
			{
				ret = DOWNLEFT;
			}

			if ( xpos-1 >= 0 && ypos-1 < map.width && !losMap[(xpos-1) + (ypos-1) * map.width] && !map.map[(xpos-1) + (ypos-1) * map.width]
				&& ( !map.obstacleMap[(xpos-1) + (ypos-1) * map.width] // check for obstacle
				|| map.obstacleMap[(xpos-1) + (ypos-1) * map.width] == 'T'
				|| map.obstacleMap[(xpos-1) + (ypos-1) * map.width] == 'B' ))
			{
				ret = UPLEFT;
			}
		}
		}
	}


	//If there are no tanks in the radar, get another place to move
	if(ret==STAY)
	{
		adjacentIndices=getAdjacentIndices(index, map.width, map.height);
		targetIndex=getTargetIndex(adjacentIndices,map,index);

		//If we didn't find a valid spot, stay where we are
		if(targetIndex==-1)
			ret=STAY;
		else
			ret=convertCoordinatesToDirection(getCoords(targetIndex,map.width,map.height),
			getCoords(index,map.width,map.height));
	}

	return ret;
}

/**
 * @author Mangesh Sakordekar
 * @par Description:
 * Generates a map showing safe positions for the tank to move
 * @param[in] map - The current state of the playfield
 * @param[in] x - x coordinate of the tank
 * @param[in] y - y coordinate of the tank
 * @return Location to attack and whether to attack
 */
void RecipeAI :: genSafeMap(int x_val, int y_val, MapData map)
{
	int x, y;

	//Check for tanks on right
	for ( x = 0, y = 0; x < myStats.tankRange && x+x_val < map.width && map.obstacleMap[x+x_val + (y_val+y)*map.width] != 'R'; ++x )
	{safeMap[x+x_val + (y_val+y)*map.width]++;}

	//Check for tanks on left
	for ( x = 0, y = 0; x > (-1 * myStats.tankRange) && x+x_val >= 0 && map.obstacleMap[x+x_val + (y_val+y)*map.width] != 'R'; --x )
	{safeMap[x+x_val + (y_val+y)*map.width]++;}

	//Check for tanks in front
	for ( x = 0, y = 0; y > (-1 * myStats.tankRange) && y+y_val >= 0 && map.obstacleMap[x+x_val + (y_val+y)*map.width] != 'R'; --y )
	{safeMap[x+x_val + (y_val+y)*map.width]++;}

	//Check for tanks at the back
	for ( x = 0, y = 0; y < myStats.tankRange && y+y_val < map.height && map.obstacleMap[x+x_val + (y_val+y)*map.width] != 'R'; ++y )
	{safeMap[x+x_val + (y_val+y)*map.width]++;}

	//Check for tanks on downright
	for ( y = 0,x = 0; x < myStats.tankRange && y <= myStats.tankRange  && y+y_val < map.height && x+x_val<map.width && map.obstacleMap[x+x_val + (y_val+y)*map.width] != 'R'; ++y, ++x )
	{safeMap[x+x_val + (y_val+y)*map.width]++;}

	//Check for tanks on downleft
	for ( y = 0,x = 0; x > (-1 * myStats.tankRange) && y <= myStats.tankRange  && y+y_val < map.height && x+x_val >= 0 && map.obstacleMap[x+x_val + (y_val+y)*map.width] != 'R'; ++y, --x )
	{safeMap[x+x_val + (y_val+y)*map.width]++;}

	//Check for tanks on up right
	for ( y = 0,x = 0; x < myStats.tankRange  && y >= (-1 * myStats.tankRange) && y+y_val >= 0 && x+x_val<map.width && map.obstacleMap[x+x_val + (y_val+y)*map.width] != 'R'; --y, ++x )
	{safeMap[x+x_val + (y_val+y)*map.width]++;}

	//Check for tanks on up left
	for ( y = 0,x = 0; x > (-1 * myStats.tankRange) && y >= (-1 * myStats.tankRange) && y+y_val >= 0 && x+x_val>=0 && map.obstacleMap[x+x_val + (y_val+y)*map.width] != 'R'; --y, --x )
	{safeMap[x+x_val + (y_val+y)*map.width]++;}
}

void RecipeAI :: markCrates(int x, int y, MapData map)
{
	for(int i = -1; i<= 1; i++)
	{
		for (int j =-1; j<=1; j++)
		{
			safeMap[(x+i) + (y+j) * map.width]++;
		}
	}
}


/**
 * @author Mangesh Sakordekar
 * @par Description:
 * Calculates whether or not not too attack, and if so where to attack
 * @param[in] map - The current state of the playfield
 * @param[in] status - The AI's tank's location, health and ID
 * @return Location to attack and whether to attack
 */
direction RecipeAI::attack ( MapData map, PositionData status )
{
	int x, y;
	direction ret = STAY;
	int minDist = map.width * map.height + 1; //Guaranteed to be greater than any real distance
	int x_val, y_val;
	x_val = status.game_x;
	y_val = status.game_y;

	if(isStuck())
	{
			
		for ( x = 0, y = 0;x+x_val < map.width && getDir(RIGHT, minDist, map, status, x_val+x, y_val + y, ret); ++x );

		//Check for tanks on left
		for ( x = 0, y = 0; x+x_val >= 0 && getDir(LEFT, minDist, map, status, x_val+x, y_val + y, ret); --x );

		//Check for tanks in front
		for ( x = 0, y = 0; y+y_val >= 0 &&  getDir(UP, minDist, map, status, x_val+x, y_val + y, ret); --y );

		//Check for tanks at the back
		for ( x = 0, y = 0; y+y_val < map.height && getDir(DOWN, minDist, map, status, x_val+x, y_val + y, ret); ++y );

		//Check for tanks on downright
		for ( y = 0,x = 0; y+y_val < map.height && x+x_val<map.width
			&& getDir(DOWNRIGHT, minDist, map, status, x_val+x, y_val + y, ret); ++y, ++x );

		//Check for tanks on downleft
		for ( y = 0,x = 0; y+y_val < map.height && x+x_val >= 0
			&& getDir(DOWNLEFT, minDist, map, status, x_val+x, y_val + y, ret); ++y, --x );

		//Check for tanks on up right
		for ( y = 0,x = 0; y+y_val >= 0 && x+x_val<map.width
			&& getDir(UPRIGHT, minDist, map, status, x_val+x, y_val + y, ret); --y, ++x );

		//Check for tanks on up left
		for ( y = 0,x = 0; y+y_val >= 0 && x+x_val>=0
			&& getDir(UPLEFT, minDist, map, status, x_val+x, y_val + y, ret); --y, --x );
		
		if(ret==STAY)
		{
			if(recentVisited[0]==(x_val-1)+y_val*map.width)
				ret=RIGHT;
			if(recentVisited[0]==(x_val+1)+y_val*map.width)
				ret=LEFT;
			if(recentVisited[0]==(x_val)+(y_val+1)*map.width)
				ret=UP;
			if(recentVisited[0]==(x_val)+(y_val-1)*map.width)
				ret=DOWN;
		}
		

	return ret;
	}
	//Check for tanks on right
	for ( x = 0, y = 0; x < myStats.tankRange  && x+x_val < map.width && getDir(RIGHT, minDist, map, status, x_val+x, y_val + y, ret); ++x );

	//Check for tanks on left
	for ( x = 0, y = 0; x > (-1 * myStats.tankRange) && x+x_val >= 0 && getDir(LEFT, minDist, map, status, x_val+x, y_val + y, ret); --x );

	//Check for tanks in front
	for ( x = 0, y = 0; y > (-1 * myStats.tankRange) && y+y_val >= 0 &&  getDir(UP, minDist, map, status, x_val+x, y_val + y, ret); --y );

	//Check for tanks at the back
	for ( x = 0, y = 0; y < myStats.tankRange  && y+y_val < map.height && getDir(DOWN, minDist, map, status, x_val+x, y_val + y, ret); ++y );

	//Check for tanks on downright
	for ( y = 0,x = 0; x < myStats.tankRange && y <= myStats.tankRange  && y+y_val < map.height && x+x_val<map.width
		&& getDir(DOWNRIGHT, minDist, map, status, x_val+x, y_val + y, ret); ++y, ++x );

	//Check for tanks on downleft
	for ( y = 0,x = 0; x > (-1 * myStats.tankRange) && y <= myStats.tankRange  && y+y_val < map.height && x+x_val >= 0
		&& getDir(DOWNLEFT, minDist, map, status, x_val+x, y_val + y, ret); ++y, --x );

	//Check for tanks on up right
	for ( y = 0,x = 0; x < myStats.tankRange  && y >= (-1 * myStats.tankRange) && y+y_val >= 0 && x+x_val<map.width
		&& getDir(UPRIGHT, minDist, map, status, x_val+x, y_val + y, ret); --y, ++x );

	//Check for tanks on up left
	for ( y = 0,x = 0; x > (-1 * myStats.tankRange) && y >= (-1 * myStats.tankRange) && y+y_val >= 0 && x+x_val>=0
		&& getDir(UPLEFT, minDist, map, status, x_val+x, y_val + y, ret); --y, --x );

	return ret;
}

void RecipeAI::genLOSMap(MapData &map,PositionData status)
{
	//Any node that wasn't marked as safe can be used to shoot at a tank
	for(unsigned int i=0;i<safeMap.size();i++)
	{
		if(safeMap[i]&&map.obstacleMap[i]!='R'&&(!map.map[i]||map.map[i]==status.id))
		{
			losMap[i]=0;
		}
		else
		{
			losMap[i]++;
		}
		
	}
}
/**
 * @author Mangesh Sakordekar
 * @par Description:
 * Checks if the current location passed is a tank, obstacle or an open space.
 * @param[in] dir - direction currently being checked
 * @param[in,out] minDist -the current closest object
 * @param[in] map - The current state of the playfield
 * @param[in] status - The AI's tank's location, health and ID
 * @param[in] x - x coordinate
 * @param[in] y - y coordinate
 * @param[in, out] ret - direction to be set
 * @return False if encountered an obstacle or tank and true otherwise
 */
bool RecipeAI::getDir(direction dir, int &minDist, MapData map, PositionData status, int x, int y, direction &ret)
{
	int minDistTemp;

	if(isStuck())
	{
		if(map.map[x + y * map.width]
			&& map.map[x + y * map.width] != status.id //And it is not you
			&& map.map[x + y * map.width] != -status.id) //And its not your projectile
		{
			minDistTemp = calcDist ( status.game_x, status.game_y, x, y );
			minDist = minDistTemp;
			ret = dir;
			return false;
		}
		return true;
	}
	if((map.map[x + y * map.width] || map.obstacleMap[x + y * map.width] == 'T' // If its a tank or a tree
		|| map.obstacleMap[x + y * map.width] == 'R' || map.obstacleMap[x + y * map.width] == 'C') //or a rock or a crate
			&& map.map[x + y * map.width] != status.id //And it is not you
			&& map.map[x + y * map.width] != -status.id) //And its not your projectile
			{
				//Calculate the distance
				minDistTemp = calcDist ( status.game_x, status.game_y, x, y );
				if( minDistTemp < minDist)
				{
					//Check for a crate
					if (map.obstacleMap[x + y * map.width] == 'C' && minDistTemp > 2)
					{
						//Look for tanks around the crate
						fullMap = map.obstacleMap;
						if(checkNeighbouringCells(x, y, map, status))
						{
							minDist = minDistTemp;
							ret = dir;
						}
					}
					//Check if its a rook or a tree
					else if(map.obstacleMap[x + y * map.width] == 'T' && map.map[x + y * map.width])
					{
						minDist = minDistTemp;
						ret = dir;
					}
					else if(map.obstacleMap[x + y * map.width] != 'T' && map.obstacleMap[x + y * map.width] != 'R' && map.obstacleMap[x + y * map.width] != 'C')
					{
						minDist = minDistTemp;
						ret = dir;
					}
    			return false;
				}

			}

  return true;
}


/**
 * @author Mangesh Sakordekar
 * @par Description:
 * Checks all the cells around the carate for another tank
 * @param[in] x - x coordinate of the crate
 * @param[in] y - y coordinate of the crate
 * @param[in] map - The current state of the playfield
 * @param[in] status - The AI's tank's location, health and ID
 * @return true if encounters a tank
 */
bool RecipeAI::checkNeighbouringCells ( int x, int y, MapData map, PositionData status )
{
	bool ret = false;
	fullMap[x + y * map.width] = 0;
	//Check all the cells around the crate
	for(int i = -1; i<= 1; i++)
	{
		for (int j =-1; j<=1; j++)
		{
			if (x+i>=0 && x+i < map.width && y+j>=0 && y+j < map.height //Check for bounds of the map
				&& (map.map[(x+i) + (y+j) * map.width] || fullMap[(x+i) + (y+j) * map.width] == 'C') //Check if its a tank
				&& map.map[(x+i) + (y+j) * map.width] != status.id //And it is not you
				&& map.map[(x+i) + (y+j) * map.width] != -status.id) //and not your projectile
				{
					if(fullMap[(x+i) + (y+j) * map.width] == 'C')
					{
						ret = checkNeighbouringCells(x+i, y+j, map, status);
					}
					else if(map.map[(x+i) + (y+j) * map.width])
					{
						return true;
					}
				}
		}
	}

	return ret;
}


/**
 * @author David Donahue
 * @par Description:
 * Calculates how many moves it will take to reach a given coordinate
 * @param[in] x1 - starting point x coordinate
 * @param[in] y1 - starting point y coordinate
 * @param[in] x2 - end point x coordinate
 * @param[in] y2 - end point y coordinate
 * @return distance to the target
 */
int RecipeAI::calcDist ( int x1, int y1, int x2, int y2 )
{
	return ( abs ( x1 - x2 ) + abs ( y1 - y2 ) );
}


int addPoint(int *pointsAvailable)
{
	*pointsAvailable-=1;
	if(*pointsAvailable>=0)
		return 1;
	else
		return 0;
}

/**
 * @author Kendric Thompson
 * @par Description:
 * Returns the attributes for the tank
 * @param[in] pointsAvailable - available points for the distribution
 * @return attributes of the tank
 */
attributes RecipeAI::setAttribute( int pointsAvailable, attributes baseStats )
{
	//options: Health, Damage, AP, Shots, Ammo, Radar, Range
	//Ranking: AP, Radar, Range, Health, Damage, Ammo, (Shots)?
	//whats the available range of pointsAvailable?
	//do I need to make this tankStats?
	attributes tankStats(0,0,0,0,0,0,0);

	//how to spend points and recheck count every time?
	
		tankStats.tankAP += addPoint(&pointsAvailable);
		tankStats.tankAP +=addPoint(&pointsAvailable);
		tankStats.tankRange +=addPoint(&pointsAvailable);
		tankStats.tankRadar +=addPoint(&pointsAvailable);
		tankStats.tankDamage +=addPoint(&pointsAvailable);


	myStats.tankAmmo=baseStats.tankAmmo;
	myStats.tankRadar=baseStats.tankRadar+tankStats.tankRadar;
	myStats.tankRange=baseStats.tankRange+tankStats.tankRange;
	myStats.tankAP=baseStats.tankAP+tankStats.tankAP;
	myStats.tankDamage=baseStats.tankDamage+tankStats.tankDamage;
	myStats.tankHealth=baseStats.tankHealth;
	myStats.tankShots=baseStats.tankShots;
	return tankStats;
}


/**
 * @author Jordan Baumeister, Kenji Johnson, Mangesh Sakordekar, Woodlin Smith
 * @par Description:
 * Updates required information, and then passes it off to move and attack 
 * functions. This info is then used to decide which action to take
 * @param[in] map - The current state of the playfield
 * @param[in] status - The AI's tank's location, health and ID
 * @return direction to move
 */
int RecipeAI::spendAP ( MapData map, PositionData status )
{

	genFullMap(map);
	apCounter++;
	if(apCounter == myStats.tankAP)
	{
		safeMode = true;
		apCounter = 0;
	}
	else
		safeMode = false;

	if(recentVisited.size()==8)
		recentVisited.erase(recentVisited.begin());

	recentVisited.push_back(status.game_y*map.width+status.game_x);

	//If the game just started, init data
	if(visitedAtLeastOnce.size()!=map.map.size())
	{
		visitedAtLeastOnce.resize(map.map.size());
		turnsSinceVisit.resize(map.map.size());
		persObsMap.resize(map.map.size());
	}

	if(visitedAtLeastOnce[status.game_y*map.width+status.game_x]==0)
	{
		visitedAtLeastOnce[status.game_y*map.width+status.game_x]=1;
	}
		

	updateData(map,status);



	spend = false;

	direction tMove = move ( map, status );
	direction tAttack = attack ( map, status );

	spend = true;


	if ( tMove == STAY && tAttack != STAY ) //If there is nowhere to move, attack
	{
		return 2;
	}

	if ( tAttack == STAY && tMove != STAY ) //If there is nowhere to attack, move
	{
		return 1;
	}

	if ( tAttack == STAY && tMove == STAY ) //If there is nothing to do, end your turn
	{
		return 3;
	}

	if ( tAttack != STAY && tMove != STAY && !safeMode) //If there is nothing to do, end your turn
	{
		return 2;
	}

	if ( tAttack != STAY && tMove != STAY && safeMode) //If there is nothing to do, end your turn
	{
		return 1;
	}

	return ( status.ap > 1 ) ? 1 : 2;
}
/**
 * @author Woodlin Smith
 * @par Description:
 * Gets all the adjacent indices to a base index.
 * @param[in] baseIndex - The index to calculate adjacency
 * @param[in] mapWidth - The map's width
 * @param[in] mapHeight - The map's height
 * @return adjIndices - the adjacent indices
 */
vector<int> RecipeAI::getAdjacentIndices(int baseIndex, int mapWidth, int mapHeight)
{
    int topRow;
    int bottomRow;
    int addoffset=2;
    int suboffset=1;
    vector<int> adjIndices;

    //Check to see if index is last item in a row or first item in a row
    if(baseIndex%mapWidth==mapWidth-1)
        addoffset=1;
    if(baseIndex%mapWidth==0)
        suboffset=0;

    for(int i=baseIndex-suboffset;i<baseIndex+addoffset;i++)
    {
            topRow=i-mapWidth;
            bottomRow=i+mapWidth;

            if(topRow>=0)
                adjIndices.push_back(topRow);
            if(bottomRow<mapWidth*mapHeight)
                adjIndices.push_back(bottomRow);
            if(i>=0 && i<mapWidth*mapHeight && i!=baseIndex)
                adjIndices.push_back(i);

    }
    return adjIndices;
}

/**
 * @author Woodlin Smith
 * @par Description:
 * Returns whether or not an index can be moved to
 * @param[in] index - The index to move to
 * @param[in] map - The map
 * @return true - the move is valid
 * @return false - the move is invalid
 */
bool RecipeAI::validMove(int index, MapData &map)
{
	for(unsigned int i=0; i<recentVisited.size();i++)
		if(recentVisited[i]==index)
			return false;

	if(persObsMap[index]=='R'||persObsMap[index]=='W')
		return false;

	return true;

}

/**
 * @author Woodlin Smith
 * @par Description:
 * Gets the index to move to, prioritiing unvisited
 * tiles first
 * @param[in] adjacentIndices - the adjacency list for the current location
 * @param[in] map - The map
 * @param[in] index - the base location
 * @return targetIndex - the index to move to
 * @return -1 - could not find an index to move to
 */
int RecipeAI::getTargetIndex(vector<int> adjacentIndices, MapData &map, int index)
{
	int unknown=0;
	int minUnknown=-1;
	int targetIndex=-1;
	int mapWidth=map.width;
	int mapHeight=map.height;
	int highPriority=-1;

	//Find any adjacent unknown tile
	for(unsigned int i=0; i<adjacentIndices.size();i++)
	{
		if(validMove(adjacentIndices[i],map)&&visitedAtLeastOnce[adjacentIndices[i]]==0)
		{
				targetIndex=adjacentIndices[i];
				return targetIndex;
		}

	}

	//Try to find the adjacent known tile with the most adjacent unknown tiles
	for(unsigned int i=0; i<adjacentIndices.size();i++)
	{
		if(validMove(adjacentIndices[i],map)&&visitedAtLeastOnce[adjacentIndices[i]])
		{
			unknown=countAdjacentUnknownNodes(adjacentIndices[i],mapWidth,mapHeight);
			if(unknown>=minUnknown)
			{
				targetIndex=adjacentIndices[i];
				minUnknown=unknown;
			}

		}
		else
		{
			//If the adjacent tile is a rock or water, just mark it as visited
			if(map.obstacleMap[adjacentIndices[i]]==87||map.obstacleMap[adjacentIndices[i]]==82)
				visitedAtLeastOnce[adjacentIndices[i]]=1;
		}

	}

	//If all tiles are known within a 2 block radius get a path to the tile with the most adjacent unvisited tiles
	if(minUnknown==0)
	{
		
		if(aiPath.empty())
		{
			highPriority=getHighestPriorityIndex(map);
			buildAIPath(index, highPriority, map);
		}

		targetIndex=aiPath.top();
		if(targetIndex==index)
			aiPath.pop();
	}

	else 
		while(!aiPath.empty())
			aiPath.pop();
	return targetIndex;
}

/**
 * @author Woodlin Smith
 * @par Description:
 * Calculates coordinates based off of an index
 * @param[in] index - the base location
 * @param[in] mapWidth - The map width
 * @param[in] mapHeight - The map's height
 * @return coords - coordinates
 */
pair<int,int> RecipeAI::getCoords(int index, int mapWidth, int mapHeight)
{
    pair<int,int> coords;

    coords.first=index%mapWidth;
    coords.second=index/mapWidth;

    return coords;
}

/**
 * @author Woodlin Smith
 * @par Description:
 * Calculates a direction to move based off of coordinates
 * @param[in] targetLocation - The place to move to
 * @param[in] currentLocation - Where we currently are
 * @return direction to move to
 */
direction RecipeAI::convertCoordinatesToDirection(pair<int,int> targetLocation, pair<int,int>currentLocation)
{
    if(currentLocation.first==targetLocation.first)
    {
        if(targetLocation.second==currentLocation.second)
            return STAY;
        else if(targetLocation.second==currentLocation.second-1)
            return UP;
        else
            return DOWN;
    }

    else if(targetLocation.first==currentLocation.first-1)
    {
        if(targetLocation.second==currentLocation.second)
            return LEFT;
        else if(targetLocation.second==currentLocation.second-1)
            return UPLEFT;
        else
            return DOWNLEFT;
    }

    else
    {
        if(targetLocation.second==currentLocation.second)
            return RIGHT;
        else if(targetLocation.second==currentLocation.second-1)
            return UPRIGHT;
        else
            return DOWNRIGHT;
    }

}


/**
 * @author Mangesh Sakordekar
 * @par Description:
 * Generates a map used for safeMode movement calculations
 * @param[in] map - the current map
 */
void RecipeAI::genFullMap ( MapData map )
{
	for( int i = 0; i<map.height; i++)
	{
		for (int j=0; j<map.width; j++)
		{
			if(map.obstacleMap[i+j*map.width])
				fullMap[i+j*map.width] = map.obstacleMap[i+j*map.width];
		}
	}
}

/**
 * @author Woodlin Smith
 * @par Description:
 * Counts the adjacent unknown nodes from a tile
 * @param[in] index - The location to calculate based off of
 * @param[in] mapWidth - the map's width
 * @param[in] mapHeight - the map's height
 * @return minUnknown - the amount of unknown nodes
 */
int RecipeAI::countAdjacentUnknownNodes( int index, int mapWidth, int mapHeight)
{
	int minUnknown=0;
	vector<int> adjacentIndices=getAdjacentIndices(index,mapWidth,mapHeight);

	for(unsigned int i=0; i<adjacentIndices.size();i++)
	{
		if(visitedAtLeastOnce[adjacentIndices[i]]==0)
			minUnknown++;
	}
	return minUnknown;
}

/**
 * @author Woodlin Smith
 * @par Description:
 * Determines if the AI got stuck on an obstacle
 * @return false - the AI is not stuck
 * @return true - the AI is stuck
 */
bool RecipeAI::isStuck()
{
	if(recentVisited.size()<4)
		return false;

	int item1=recentVisited[0];
	int item2=recentVisited[1];

	for(unsigned int i=0;i<4;i=i+2)
	{
		item1=recentVisited[i];
		item2=recentVisited[i+1];
	}

	if(item1==recentVisited[0]&&item2==recentVisited[1]&&(item1!=item2))
		return true;
	return false;
}

/**
 * @author Woodlin Smith
 * @par Description:
 * Returns the known index with the highest amount of adjacent unknown indiices
 * @param[in] map - the map
 * @return index - the index with the highest amount of adjacent unkown indices
 */
int RecipeAI::getHighestPriorityIndex(MapData &map)
{
	int index;
	int minUnknown=0;
	int unknown;
	for(unsigned int i=0; i<visitedAtLeastOnce.size();i++)
	{
		if(visitedAtLeastOnce[i]&&validMove(i, map))
		{
			unknown=countAdjacentUnknownNodes(i,map.width, map.height);
			if(unknown>minUnknown)
			{
				minUnknown=unknown;
				index=i;
			}
		}
	}
	return index;
}

/**
 * @author Woodlin Smith
 * @par Description:
 * Calculates a path to a tile
 * @param[in] currLoc - our current location
 * @param[in] targetLoc - our goal
 * @param[in] map - the game map
 */
void RecipeAI::buildAIPath(int currLoc, int targetLoc, MapData &map)
{
	if(targetLoc==currLoc||targetLoc==-1)
		return;

	vector<int> targAdj=getAdjacentIndices(targetLoc,map.width,map.height);
	vector<int> validMoves;
	int index=-1;
	int minTime=100000;
	pair<int,int> currCoords=getCoords(currLoc,map.width,map.height);
	pair<int,int> targetCoords=getCoords(targetLoc,map.width,map.height);
	pair<int,int> adjCoords;
	int dist;
	int minDist=calcDist(currCoords.first,currCoords.second,targetCoords.first,targetCoords.second);

	

	if(aiPath.empty())
		aiPath.push(targetLoc);

	

	for(unsigned int i=0; i<targAdj.size();i++)
	{
		//Calculate the closest visited spot
		if((map.obstacleMap[targAdj[i]]!='R')&&(map.obstacleMap[targAdj[i]]!='W')
			&&visitedAtLeastOnce[targAdj[i]])
		{
			validMoves.push_back(targAdj[i]);
			adjCoords=getCoords(targAdj[i],map.width,map.height);
			dist=calcDist(currCoords.first,currCoords.second,adjCoords.first,adjCoords.second);
			if((turnsSinceVisit[targAdj[i]]<minTime)||(minTime==1000000&&dist<=minDist))
			{
				minTime=turnsSinceVisit[targAdj[i]];
				minDist=dist;
				index=targAdj[i];
			}
		
		}

	}
	if(index!=-1&&index!=currLoc)
		aiPath.push(index);
	buildAIPath(currLoc,index,map);
}

/**
 * @author Woodlin Smith
 * @par Description:
 * Updates the data that needs to change turn to turn
 * @param[in] index - The location to calculate based off of
 * @param[in] map - the game map
 * @param[in] status - our current status info
 */
void RecipeAI::updateData(MapData &map, PositionData status)
{
	for(unsigned int i=0; i<map.map.size();i++)
	{
		if(i==unsigned(status.game_x+status.game_y*map.width))
			turnsSinceVisit[i]=0;
		else 
			turnsSinceVisit[i]++;

		if(persObsMap[i]!=map.obstacleMap[i]&&map.obstacleMap[i]!=0)
		{
			persObsMap[i]=map.obstacleMap[i];
		}
	}

}





#ifdef DYNAMIC
extern "C" //required for runtime linking
{
	Actor* maker()
	{
		return new RecipeAI;
	}
}
#endif
