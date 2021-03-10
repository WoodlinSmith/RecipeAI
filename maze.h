/********************************************************************//**
 * @file
 ***********************************************************************/
#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <vector>
#include <utility>           // For pair, make_pair
#include <ctime>             // time
#include <cstdlib>           // for srand, rand
#include "disjointBySize.h"

/********************************************************************//**
 * @class Maze
 **********************************************************************/
class Maze
{
   std::vector<std::pair<int,int>> edges;
   int Cols, Rows;
public:
   Maze(int, int);

   void print(std::string *);
};
#endif
