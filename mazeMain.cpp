#include <iostream>
#include <string>
#include "maze.h"

#define ROWS 10
#define COLS 20

void usage(char *argv[])
{
   std::cout << argv[0] << "[cols rows]" << std::endl;
}

int main(int argc, char *argv[])
{
   int rows = ROWS;
   int cols = COLS;

   if (argc != 1 && argc != 3)
      usage(argv);
   else if (argc == 3)
   {
      rows = std::stoi(argv[1]);
      cols = std::stoi(argv[2]);
   }

   std::cout << "WIDTH " << cols * 2 << std::endl;
   std::cout << "HEIGHT " << rows * 2 << std::endl;
   std::cout << "MAP" << std::endl;
   Maze maze(cols, rows);

   return 0;
}
