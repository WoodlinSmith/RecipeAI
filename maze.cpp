/********************************************************************//**
 * @file
 ***********************************************************************/
#include "maze.h"

void removeEdge(std::string *map, int v, int w, int width)
{
   int diff = v - w;
   int row = v / width * 2;
   int col = v % width * 2;
   if (diff == 1)
      map[row][col-1] = 'x';
   else if (diff == -1)
      map[row][col+1] = 'x';
   else if (diff == width)
      map[row-1][col] = 'x';
   else if (diff == -width)
      map[row+1][col] = 'x';
   else
      std::cout << "Bad edge removal(" << v << ", " << w << ", " << width << ")\n";
}

Maze::Maze(int columns, int rows) : Cols(columns), Rows(rows)
{
   srand(time(NULL));
   // Cells with odd column or row (or both) values are walls
   for (int row = 0 ; row < Rows ; row++)
      for (int col = 0 ; col < Cols ; col++)
      {
         int index = row * Cols + col;
         if (row != Rows-1)
            edges.push_back(std::pair<int,int>(index, index+Cols));
         if (col != Cols-1)
            edges.push_back(std::pair<int,int>(index, index+1));
      }

   std::string *asciiRows = new std::string[Rows*2];
   
   for (int row = 0 ; row < Rows ; row++)
      for (int col = 0 ; col < Cols ; col++)
      {
         asciiRows[2*row].push_back('x');
         asciiRows[2*row].push_back('R');
         asciiRows[2*row+1].push_back('R');
         asciiRows[2*row+1].push_back('R');
      }

   // Each cell is a disjoint set to start
   DisjointSet ds;
   ds.makeSet(columns * rows);

   // start randomly picking and removing edges and their associated walls
   int edgesLeft = edges.size();
   while (ds.setCount() > 1)
   {
      int deletedEdge = rand() % edgesLeft;
      int v = edges[deletedEdge].first;
      int w = edges[deletedEdge].second;
      if (ds.findSet(v) != ds.findSet(w))
      {
         ds.Union(v, w);
         removeEdge(asciiRows, v, w, Cols);
         std::swap(edges[deletedEdge], edges[--edgesLeft]);
      }
   }
   print(asciiRows);
}

void Maze::print(std::string *asciiRows)
{
   for (int row = 0 ; row < Rows*2 ; row++)
      std::cout << asciiRows[row] << std::endl;
}
