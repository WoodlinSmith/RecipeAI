/****
 * Author: Timothy Ford
 *
 * Date: Spring 2019
 *
 * Professor: Dr. Hinker
 *
 * Description: This is a utility program that generates a usable
 * map.txt file for the tank platform. It fills a map of the desired
 * size and than calculates the structure of the map off of the random
 * integers given. It then adds a couple more interesting structurdes
 * for rock and water and then outputs that as well as randomized start
 * points for the tanks.
 *
 *
 * Compilation/Build:
 *
 * In order to make this program from the current directory, a make
 * file is included so just type make.
 *
 * In order to use this with the platform, you'll want to run 'make mapGen'
 * from the same directory you would build the platform from.
 *
 *
 * Usage:
 *
 * (Max width, height: 50,21)
 *
 * Defaults (grass map, w = 30, h = 13): ./mapGen
 * Seeded map (w = 30, h = 13): ./mapGen [seed]
 * Custom width and height: ./mapGen [seed] [w] [h]
 * Custom number of tanks (max 8): ./mapGen [seed] [w] [h] [numTanks]
 *
 * Bugs:
 * - Despite my best efforts, tanks can randomly spawn right next to
 *      each other :(
 */

#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>
#include <time.h>

//Helpful things we might want
#define T 1
#define F 0
#define DEFAULTW 30
#define DEFAULTH 13

//the things that can be placed on our map
#define GRASS 'x'
#define TREE 'T'
#define BUSH 'B'
#define CRATE 'C'
#define ROCK 'R'
#define WATER 'W'

using namespace std;


void fillDefaultMap ( int width, int height, vector<vector<char>> mapC );
void outputMap ( int width, int height, vector<vector<char>> map, int numTanks );
void fillNormalMap ( int width, int height, vector<vector<int>> map, vector<vector<char>> mapC, int numTanks );
bool checkIsolatedRock ( const int i, const int j, int kernel, vector<vector<char>> mapC );
bool checkIsolatedWater ( const int i, const int j, int kernel, vector<vector<char>> mapC );
double distance ( vector<int> a, int b, int c );


int main ( int argc, char* argv[] )
{
	int numTanks = 8;
	int seed;
	int width, height;

	if ( argc == 1 )
	{
		cout << "Usage: ./mapGen [seed] [w] [h] [numTanks]" << endl
		     << "All parameters are required" << endl;

		vector<int> a ( DEFAULTH, 0 );
		vector<vector<int>> map ( DEFAULTW, a );

		vector<char> b ( DEFAULTW );
		vector<vector<char>> mapC ( DEFAULTH, b );

		fillDefaultMap ( DEFAULTW, DEFAULTH, mapC );
	}
	else if ( argc == 2 )
	{
		vector<int> a ( DEFAULTW, 0 );
		vector<vector<int>> map ( DEFAULTH, a );

		vector<char> b ( DEFAULTW );
		vector<vector<char>> mapC ( DEFAULTH, b );

		seed = atoi ( argv[1] );
		srand ( seed );

		fillNormalMap ( DEFAULTW, DEFAULTH, map, mapC, numTanks );
	}
	else if ( argc == 4 )
	{
		width = atoi ( argv[2] );
		height = atoi ( argv[3] );

		vector<int> a ( width, 0 );
		vector<vector<int>> map ( height, a );

		vector<char> b ( width );
		vector<vector<char>> mapC ( height, b );

		seed = atoi ( argv[1] );
		srand ( seed );

		fillNormalMap ( width, height, map, mapC, numTanks );
	}
	else if ( argc == 5 )
	{
		width = atoi ( argv[2] );
		height = atoi ( argv[3] );
		numTanks = atoi ( argv[4] );

		vector<int> a ( width, 0 );
		vector<vector<int>> map ( height, a );

		vector<char> b ( width );
		vector<vector<char>> mapC ( height, b );

		seed = atoi ( argv[1] );
		srand ( seed );

		fillNormalMap ( width, height, map, mapC, numTanks );
	}

	return 0;
}




/**
 * @brief Generates an all grass map with starting locations for 8 tanks
 *
 * @param width
 * @param height
 * @param map
 * @param mapC
 */
void fillDefaultMap ( int width, int height, vector<vector<char>> mapC )
{
	int i = 0, j = 0;
	int numTanks = 8;

	for ( i = 0; i < DEFAULTH; i++ )
	{
		for ( j = 0; j < DEFAULTW; j++ )
		{
			mapC[i][j] = 'x';
		}
	}

	outputMap ( width, height, mapC, numTanks );
}

/**
 * @brief Generates a map full of obstacles. Something that you might actually want.
 * The really horrific long ifs generate 'structures' that are more interesting than
 * just random isolated rocks and water.
 *
 * @param width
 * @param height
 * @param map
 * @param mapC
 * @param numTanks
 */
void fillNormalMap ( int width, int height, vector<vector<int>> map, vector<vector<char>> mapC, int numTanks )
{
	int i = 0, j = 0;
	int chance = 0;
	int xAxis = 0, yAxis = 0;
	int xCoord = 0, yCoord = 0;

	//generate original number matrix

	for ( i = 0; i < height; i++ )
	{
		for ( j = 0; j < width; j++ )
		{
			map[i][j] = rand() % 150;
		}
	}

	for ( i = 0; i < height; i++ )
	{
		for ( j = 0; j < width; j++ )
		{
			if ( map[i][j] >= 7 && map[i][j] < 14 ) //range of 10
			{
				mapC[i][j] = TREE;
			}
			else if ( map[i][j] >= 4 && map[i][j] < 9 ) //range of 10
			{
				mapC[i][j] = ROCK;
			}
			else if ( map[i][j] >= 0 && map[i][j] < 4 ) //range of 5
			{
				mapC[i][j] = CRATE;
			}
			else if ( map[i][j] >= 14 && map[i][j] < 20 ) //range of 10
			{
				mapC[i][j] = BUSH;
			}
			else if ( map[i][j] >= 20 && map[i][j] < 22 ) //range of 10
			{
				mapC[i][j] = WATER;
			}
			else //range of 45
			{
				mapC[i][j] = GRASS;
			}
		}
	}

	for ( i = 2; i < ( height - 2 ); i++ )
	{
		for ( j = 2; j < ( width - 2 ); j++ )
		{
			if ( mapC[i][j] == ROCK )
			{
				//check if the rock is isolated

				if ( checkIsolatedRock ( i, j, 1, mapC ) == true )
				{
					chance = rand() % 70;

					if ( chance < 33 )
					{
						xAxis = rand() % 3;
						yAxis = rand() % 3;

						while ( xAxis == 1 && yAxis == 1 )
						{
							xAxis = rand() % 3;
							yAxis = rand() % 3;
						}

						xAxis -= 1;
						yAxis -= 1;

						xCoord = i + xAxis;
						yCoord = j + yAxis;

						mapC[xCoord][yCoord] = ROCK;
					}
					else if ( chance < 43 )
					{
						mapC[i - 1][j] = ROCK;
						mapC[i + 1][j + 1] = ROCK;
						mapC[i + 1][j] = ROCK;
					}
					else if ( chance < 48 )
					{
						mapC[i - 2][j] = ROCK;
						mapC[i - 1][j] = ROCK;
						mapC[i + 1][j + 1] = ROCK;
						mapC[i + 1][j] = ROCK;
						mapC[i][j - 2] = ROCK;
						mapC[i][j - 1] = ROCK;
					}
					else if ( chance < 53 )
					{
						mapC[i][j - 2] = ROCK;
						mapC[i][j - 1] = ROCK;
						mapC[i - 1][j - 1] = ROCK;
						mapC[i][j + 1] = ROCK;
						mapC[i - 2][j] = ROCK;
						mapC[i - 1][j] = ROCK;
					}
				}

				if ( mapC[i][j] == WATER )
				{
					if ( checkIsolatedWater ( i, j, 1, mapC ) == true )
					{
						chance = rand() % 70;

						if ( chance < 33 )
						{
							xAxis = rand() % 3;
							yAxis = rand() % 3;

							while ( xAxis == 1 && yAxis == 1 )
							{
								xAxis = rand() % 3;
								yAxis = rand() % 3;
							}

							xAxis -= 1;
							yAxis -= 1;

							xCoord = i + xAxis;
							yCoord = j + yAxis;

							mapC[xCoord][yCoord] = WATER;
						}
						else if ( chance < 43 )
						{
							mapC[i - 1][j] = WATER;
							mapC[i + 1][j + 1] = WATER;
							mapC[i + 1][j] = WATER;
						}
						else if ( chance < 48 )
						{
							mapC[i - 2][j] = WATER;
							mapC[i - 1][j] = WATER;
							mapC[i + 1][j + 1] = WATER;
							mapC[i + 1][j] = WATER;
							mapC[i][j - 2] = WATER;
							mapC[i][j - 1] = WATER;
						}
						else if ( chance < 53 )
						{
							mapC[i][j - 2] = WATER;
							mapC[i][j - 1] = WATER;
							mapC[i - 1][j - 1] = WATER;
							mapC[i][j + 1] = WATER;
							mapC[i - 2][j] = WATER;
							mapC[i - 1][j] = WATER;
						}
					}


				}


			}
		}
	}

	outputMap ( width, height, mapC, numTanks );
}



/**
 * @brief Checks to see if a rock is isolated on the map (no other objects around)
 *
 * @param i
 * @param j
 * @param kernel
 * @param map
 * @return true
 * @return false
 */
bool checkIsolatedRock ( const int i, const int j, int kernel, vector<vector<char>> mapC )
{
	int k = 0, z = 0, count = 0;

	for ( k = -kernel; k <= kernel; k++ )
	{
		for ( z = -kernel; z <= kernel; z++ )
		{
			if ( mapC[i + k][j + z] == ROCK )
			{
				count++;
			}
		}
	}

	if ( count > 0 )
	{
		return false;
	}

	return true;
}


/**
 * @brief checks to see if water is isolated on the map (no other water around)
 *
 * @param i
 * @param j
 * @param kernel
 * @param map
 * @return true
 * @return false
 */
bool checkIsolatedWater ( const int i, const int j, int kernel, vector<vector<char>> mapC )
{
	int k = 0, z = 0, count = 0;

	for ( k = -kernel; k <= kernel; k++ )
	{
		for ( z = -kernel; z <= kernel; z++ )
		{
			if ( mapC[i + k][j + z] == WATER )
			{
				count++;
			}
		}
	}

	if ( count > 0 )
	{
		return false;
	}

	return true;
}


/**
 * @brief Handles the output format for the map as well as the random spawns.
 *
 * @param width
 * @param height
 * @param map
 * @param numTanks
 */
void outputMap ( int width, int height, vector<vector<char>> map, int numTanks )
{
	int i, j;
	unsigned int ju = 0;
	int x, y;
	ofstream fout;
	vector<int> temp;
	vector<vector<int>> coords;
	fout.open ( "map.txt" );

	srand ( time ( NULL ) );

	fout << "WIDTH " << width << endl;
	fout << "HEIGHT " << height << endl;
	fout << "MAP" << endl;

	for ( i = 0; i < height; i++ )
	{
		for ( j = 0; j < width; j++ )
		{
			fout << map[i][j];
		}

		fout << endl;
	}

	fout << endl;

	x = rand() % width;
	y = rand() % height;

	temp.push_back ( x );
	temp.push_back ( y );

	coords.push_back ( temp );

	for ( int i = 0; i < numTanks; i++ )
	{
		x = rand() % width;
		y = rand() % height;

		for ( ju = 0; ju < coords.size(); ju++ )
		{
			while ( distance ( coords[ju], x, y ) < 3 )
			{
				x = rand() % width;
				y = rand() % height;
			}
		}

		temp[0] = x;
		temp[1] = y;

		coords.push_back ( temp );
	}

	for ( i = 0; i < numTanks; i++ )
	{
		fout << "START " << coords[i][0] << " " << coords[i][1] << endl;
	}

	fout.close();
}

/**
 * @brief Calculates the distance between two points. One point is fed as a vector
 * and the other is fed as two separate integers.
 *
 * @param a
 * @param b
 * @param c
 * @return double
 */
double distance ( vector<int> a, int b, int c )
{
	double x = fabs ( a[0] - b );
	double y = fabs ( a[1] - c );

	x = x * x;
	y = y * y;

	x = sqrt ( x + y );

	return x;
}
